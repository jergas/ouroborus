#!/usr/bin/env python3
"""Harvest text and source chips from a live browser tab.

Connects to a running browser via Chrome DevTools Protocol (CDP) for
Chromium or WebDriver BiDi for Firefox, finds a tab matching a URL
pattern, scrolls to load lazy content, and dumps the full innerText
and optionally the HTML source.

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

DEFAULT_CDP_PORT = 9222
DEFAULT_BIDI_PORT = 9223
DEFAULT_PATTERN = "gemini.google.com/app/"
CHIPS_SELECTOR = ".deep-research-source-lists"


# ---------------------------------------------------------------------------
# Shared helpers
# ---------------------------------------------------------------------------

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


# ---------------------------------------------------------------------------
# Firefox WebDriver BiDi backend
# ---------------------------------------------------------------------------

_bidi_counter = 0

def bidi_cmd(ws, method, params):
    global _bidi_counter
    _bidi_counter += 1
    msg = {"id": _bidi_counter, "method": method, "params": params or {}}
    ws.send(json.dumps(msg))
    return _bidi_counter


def bidi_recv_result(ws, target_id, timeout=30):
    deadline = time.time() + timeout
    while time.time() < deadline:
        ws.settimeout(0.5)
        try:
            msg = json.loads(ws.recv())
            if msg.get("id") == target_id:
                if "error" in msg:
                    raise RuntimeError(f"BiDi error: {msg['error']}: {msg.get('message','')[:200]}")
                return msg.get("result")
        except websocket.WebSocketTimeoutException:
            continue
    return None


def bidi_connect(port, pattern):
    """Connect to Firefox via BiDi, find matching context, return (ws, context_id).

    Firefox exposes WebDriver BiDi directly at ws://localhost:PORT/session:
    the first command is session.new (no prior HTTP handshake), then
    browsingContext.getTree lists the open tabs.
    """
    print(f"Connecting to Firefox BiDi on port {port}...")
    ws_url = f"ws://localhost:{port}/session"
    try:
        ws = websocket.create_connection(ws_url, timeout=15, suppress_origin=True)
    except Exception as e:
        raise RuntimeError(
            f"Could not connect to {ws_url}: {e}. "
            "Ensure Firefox was launched with --remote-debugging-port."
        )

    rid = bidi_cmd(ws, "session.new", {
        "capabilities": {"alwaysMatch": {"browserName": "firefox"}}})
    result = bidi_recv_result(ws, rid)
    session_id = (result or {}).get("sessionId", "")
    print(f"Session {session_id[:12]}...")

    rid = bidi_cmd(ws, "browsingContext.getTree", {})
    result = bidi_recv_result(ws, rid)
    contexts = result.get("contexts", []) if result else []

    def flatten(ctxs):
        for c in ctxs:
            yield c
            yield from flatten(c.get("children", []))

    target_ctx = None
    for ctx in flatten(contexts):
        if pattern in ctx.get("url", ""):
            target_ctx = ctx
            break
    # Fall back to any non-blank context if the pattern doesn't match
    # (Firefox 155 omits the type field from getTree results).
    if target_ctx is None:
        for ctx in flatten(contexts):
            url = ctx.get("url", "")
            if url and url != "about:blank":
                target_ctx = ctx
                break

    if target_ctx is None:
        ws.close()
        raise RuntimeError(
            f"No usable tab in Firefox on port {port}. "
            "Open a Gemini conversation in the debug Firefox first."
        )

    ctx_id = target_ctx["context"]
    print(f"Found context {ctx_id[:12]}... [{target_ctx.get('url', '')[:80]}]")
    return ws, ctx_id


def bidi_eval(ws, ctx_id, expr):
    """Evaluate JS in a browsing context; returns the value or None.

    Firefox's script.evaluate requires an explicit awaitPromise and only
    accepts resultOwnership of 'none' or 'root'.
    """
    rid = bidi_cmd(ws, "script.evaluate", {
        "expression": expr,
        "target": {"context": ctx_id},
        "resultOwnership": "none",
        "awaitPromise": False,
    })
    result = bidi_recv_result(ws, rid)
    if result and "result" in result and isinstance(result["result"], dict):
        return result["result"].get("value")
    return None


def bidi_scroll_to_bottom(ws, ctx_id, passes=40, slow_passes=10):
    total = bidi_eval(ws, ctx_id, "document.body.scrollHeight") or 0
    for _ in range(passes):
        cur = bidi_eval(ws, ctx_id,
                        "window.scrollTo(0, document.body.scrollHeight); document.body.scrollHeight")
        if cur and cur > total:
            total = cur
        time.sleep(0.4)
    for _ in range(slow_passes):
        bidi_eval(ws, ctx_id, "window.scrollTo(0, document.body.scrollHeight)")
        time.sleep(0.7)


def harvest_bidi(ws, ctx_id):
    """Harvest text, chips, and HTML from a Firefox BiDi context."""
    url = bidi_eval(ws, ctx_id, "document.location.href") or ""
    print(f"Current URL: {url}")

    print("Scrolling to load full content...")
    bidi_scroll_to_bottom(ws, ctx_id)

    bidi_eval(ws, ctx_id, "window.scrollTo(0,0)")
    time.sleep(1)

    print("Extracting text...")
    text = bidi_eval(ws, ctx_id, "document.body.innerText") or ""

    print("Extracting source chips (best effort)...")
    chips_js = (
        f"JSON.stringify([...document.querySelectorAll('{CHIPS_SELECTOR}')]"
        ".map(el => {"
        "  const t = el.innerText.trim();"
        "  return t ? {text: t, html: el.innerHTML.slice(0, 600)} : null;"
        "}).filter(Boolean))"
    )
    raw_chips = bidi_eval(ws, ctx_id, chips_js)
    try:
        chips = json.loads(raw_chips) if raw_chips else []
    except (json.JSONDecodeError, TypeError):
        chips = []

    html = bidi_eval(ws, ctx_id, "document.documentElement.outerHTML") or ""
    return text, chips, html


# ---------------------------------------------------------------------------
# Launch commands
# ---------------------------------------------------------------------------

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


def launch_firefox(port, profile_dir, url=None):
    cmd = f"firefox --remote-debugging-port {port} -profile {profile_dir}"
    if url:
        cmd += f" {url}"
    return cmd


def main(argv=None):
    parser = argparse.ArgumentParser(
        description="Harvest text from a live browser tab via CDP or BiDi."
    )
    sub = parser.add_subparsers(dest="action")

    harvest_p = sub.add_parser("harvest", help="Extract text and chips from a matching tab")
    harvest_p.add_argument("--browser", choices=["chromium", "firefox"], default="chromium",
                           help="Browser backend (default: chromium)")
    harvest_p.add_argument("--port", type=int, default=None,
                           help="Debug port (default: 9222 for chromium, 9223 for firefox)")
    harvest_p.add_argument("--pattern", default=DEFAULT_PATTERN,
                           help="URL substring to match (default: gemini.google.com/app/)")
    harvest_p.add_argument("--out", type=Path, help="Output text file")
    harvest_p.add_argument("--chips-out", type=Path, help="Output source-chips JSON file")
    harvest_p.add_argument("--html-out", type=Path, help="Output HTML snapshot file")

    launch_p = sub.add_parser("launch", help="Print the command to launch the browser")
    launch_p.add_argument("--browser", choices=["chromium", "firefox"], default="chromium")
    launch_p.add_argument("--port", type=int, default=None)
    launch_p.add_argument("--profile-dir", default=None,
                          help="Profile directory (default: /tmp/opencode/gemini-profile for chromium)")
    launch_p.add_argument("--url", help="Optional URL to open")

    args = parser.parse_args(argv)

    if args.action == "launch":
        browser = getattr(args, "browser", "chromium")
        port = args.port or (DEFAULT_CDP_PORT if browser == "chromium" else DEFAULT_BIDI_PORT)
        profile = args.profile_dir or f"/tmp/opencode/gemini-{browser}"
        if browser == "chromium":
            print(launch_chromium(port, profile, args.url))
        else:
            print(launch_firefox(port, profile, args.url))
        return 0

    if args.action != "harvest":
        parser.print_help()
        return 1

    browser = getattr(args, "browser", "chromium")
    port = args.port or (DEFAULT_CDP_PORT if browser == "chromium" else DEFAULT_BIDI_PORT)

    try:
        if browser == "firefox":
            ws, ctx_id = bidi_connect(port, args.pattern)
            try:
                text, chips, html = harvest_bidi(ws, ctx_id)
            finally:
                ws.close()
        else:
            ws = cdp_connect(port, args.pattern)
            try:
                text, chips, html = harvest_cdp(ws)
            finally:
                ws.close()
    except (RuntimeError, ConnectionRefusedError, OSError) as e:
        print(f"Error: {e}", file=sys.stderr)
        return 1

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
        print("\nNo source chips found.")

    if args.html_out:
        args.html_out.write_text(html)
        print(f"Saved HTML snapshot ({len(html)} chars) to {args.html_out}")

    return 0


if __name__ == "__main__":
    sys.exit(main())
