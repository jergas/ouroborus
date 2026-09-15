#!/usr/bin/env python3
"""Harvest text and source chips from a live browser tab.

Connects to a running browser via the Chrome DevTools Protocol (CDP),
finds a tab matching a URL pattern, scrolls to load lazy content,
and dumps the full innerText and optionally the HTML source.

Designed for Gemini conversations but works on any page with
lazy-loaded text content.
"""
import argparse
import json
import sys
import time
import urllib.request
from pathlib import Path

import websocket

DEFAULT_CDP = "http://localhost:9222"
DEFAULT_PATTERN = "gemini.google.com/app/"
CHIPS_SELECTOR = "deep-research-source-lists"


def http_get(url):
    with urllib.request.urlopen(url, timeout=5) as r:
        return json.loads(r.read())


def find_tab(base_url, pattern, tab_type="page"):
    pages = http_get(f"{base_url}/json/list")
    for p in pages:
        if p.get("type") != tab_type:
            continue
        if pattern in p.get("url", ""):
            return p["id"], p["url"]
    return None, None


def cdp_connect(port, pattern):
    base = f"http://localhost:{port}"
    tid, url = find_tab(base, pattern)
    if tid is None:
        raise RuntimeError(
            f"No tab matching '{pattern}' on port {port}. "
            "Launch the browser with --remote-debugging-port and navigate to the page."
        )
    ws_url = f"ws://localhost:{port}/devtools/page/{tid}"
    ws = websocket.create_connection(ws_url, timeout=15, suppress_origin=True)
    print(f"Connected to tab {tid[:12]}... [{url}]")
    return ws


def cdp_send(ws, method, params=None, id_=None):
    if id_ is None:
        cdp_send.counter += 1
        id_ = cdp_send.counter
    msg = {"id": id_, "method": method}
    if params:
        msg["params"] = params
    ws.send(json.dumps(msg))
    return id_
cdp_send.counter = 0


def cdp_recv(ws, target_id, timeout=30):
    deadline = time.time() + timeout
    while time.time() < deadline:
        ws.settimeout(0.5)
        try:
            msg = json.loads(ws.recv())
            if msg.get("id") == target_id:
                return msg
        except websocket.WebSocketTimeoutException:
            continue
    return None


def cdp_eval(ws, expr, return_by_value=True):
    rid = cdp_send(ws, "Runtime.evaluate",
                   {"expression": expr, "returnByValue": return_by_value})
    res = cdp_recv(ws, rid)
    if res and "result" in res and "result" in res["result"]:
        return res["result"]["result"].get("value")
    return None


def scroll_to_bottom(ws, passes=40, slow_passes=10):
    total = cdp_eval(ws, "document.body.scrollHeight") or 0
    for _ in range(passes):
        cur = cdp_eval(ws, "window.scrollTo(0, document.body.scrollHeight); document.body.scrollHeight")
        if cur and cur > total:
            total = cur
        time.sleep(0.4)
    for _ in range(slow_passes):
        cdp_eval(ws, "window.scrollTo(0, document.body.scrollHeight)")
        time.sleep(0.7)


def harvest_cdp(ws):
    cdp_send(ws, "Page.enable")
    cdp_send(ws, "Runtime.enable")

    url = cdp_eval(ws, "document.location.href") or ""
    print(f"Current URL: {url}")

    print("Scrolling to load full content...")
    scroll_to_bottom(ws)

    cdp_eval(ws, "window.scrollTo(0,0)")
    time.sleep(1)

    print("Extracting text...")
    text = cdp_eval(ws, "document.body.innerText") or ""

    print("Extracting source chips (best effort)...")
    chips_js = (
        f"JSON.stringify([...document.querySelectorAll('{CHIPS_SELECTOR}')]"
        ".map(el => {"
        "  const t = el.innerText.trim();"
        "  return t ? {text: t, html: el.innerHTML.slice(0, 600)} : null;"
        "}).filter(Boolean))"
    )
    raw_chips = cdp_eval(ws, chips_js)
    try:
        chips = json.loads(raw_chips) if raw_chips else []
    except (json.JSONDecodeError, TypeError):
        chips = []

    html = cdp_eval(ws, "document.documentElement.outerHTML", return_by_value=True) or ""
    return text, chips, html


def launch_chromium(port, profile_dir, url=None):
    cmd = (
        f"chromium --ozone-platform=wayland --ozone-platform-hint=wayland "
        f"--password-store=gnome-libsecret "
        f"--enable-features=TouchpadOverscrollHistoryNavigation "
        f"--user-data-dir={profile_dir} "
        f"--remote-debugging-port={port} "
        f"--remote-allow-origins=*"
    )
    if url:
        cmd += f" {url}"
    return cmd


def main(argv=None):
    parser = argparse.ArgumentParser(
        description="Harvest text from a live browser tab via CDP."
    )
    sub = parser.add_subparsers(dest="action")

    harvest_p = sub.add_parser("harvest", help="Extract text and chips from a matching tab")
    harvest_p.add_argument("--port", type=int, default=9222, help="CDP port (default 9222)")
    harvest_p.add_argument("--pattern", default=DEFAULT_PATTERN,
                           help="URL substring to match (default: gemini.google.com/app/)")
    harvest_p.add_argument("--out", type=Path, help="Output text file")
    harvest_p.add_argument("--chips-out", type=Path, help="Output source-chips JSON file")
    harvest_p.add_argument("--html-out", type=Path, help="Output HTML snapshot file")

    launch_p = sub.add_parser("launch", help="Print the command to launch the browser")
    launch_p.add_argument("--browser", choices=["chromium"], default="chromium")
    launch_p.add_argument("--port", type=int, default=9222)
    launch_p.add_argument("--profile-dir", default="/tmp/opencode/gemini-profile",
                          help="Persistent profile directory")
    launch_p.add_argument("--url", help="Optional URL to open")

    args = parser.parse_args(argv)

    if args.action == "launch":
        if args.browser == "chromium":
            print(launch_chromium(args.port, args.profile_dir, args.url))
        return 0

    if args.action != "harvest":
        parser.print_help()
        return 1

    try:
        ws = cdp_connect(args.port, args.pattern)
    except RuntimeError as e:
        print(f"Error: {e}", file=sys.stderr)
        return 1

    try:
        text, chips, html = harvest_cdp(ws)
    finally:
        ws.close()

    if args.out:
        args.out.write_text(text)
        print(f"Saved {len(text)} chars to {args.out}")
    else:
        print(f"\n--- TEXT ({len(text)} chars) ---\n")
        print(text[:5000])
        if len(text) > 5000:
            print(f"\n... ({len(text) - 5000} more chars)")

    if chips:
        chips_file = args.chips_out or Path("source_chips.json")
        chips_file.write_text(json.dumps(chips, indent=2))
        print(f"\nSaved {len(chips)} source chip sections to {chips_file}")
    else:
        print("\nNo source chips found (expected in Chromium; paste manually).")

    if args.html_out:
        args.html_out.write_text(html)
        print(f"Saved HTML snapshot ({len(html)} chars) to {args.html_out}")

    return 0


if __name__ == "__main__":
    sys.exit(main())
