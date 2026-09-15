# Harvest Tools

Reusable scripts for extracting content from live browser sessions. Currently supports the Chrome DevTools Protocol (CDP) for Chromium; Firefox WebDriver BiDi support is planned.

## Quick start

**Launch a dedicated Chromium instance** (separate profile, debug port open):

```sh
python3 .memory/tools/harvest.py launch --port 9222 --profile-dir /tmp/opencode/gemini-profile
```

Log in to Gemini in that window, navigate to your conversation, then harvest:

```sh
.venv/bin/python .memory/tools/harvest.py harvest --port 9222 --out /tmp/output.txt
```

## Why a separate profile?

The browser must be started with `--remote-debugging-port` — you cannot attach to an already-running instance that lacks the flag. A dedicated profile keeps the agent's view scoped to only what you log into there, avoids disrupting your daily browsing, and lets you nuke/relogin without affecting bookmarks or cookies.

To run everything under one profile and give the agent full access to all your tabs, launch your daily browser with the debug port and point the tool at it via `--port`. The tradeoff: everything reachable on that port is controllable (all tabs, cookies, passwords). On a single-user machine this is your call, but be aware.

## Can two profiles run at the same time?

Yes. Each Chromium instance needs its own `--user-data-dir` and `--remote-debugging-port`. Different directories + different ports = side-by-side instances. Same profile directory cannot be shared by two running Chromium processes (the second launch hands off to the first).

## Current Chromium instance

The live agent session uses:

```
chromium --ozone-platform=wayland --ozone-platform-hint=wayland \
  --password-store=gnome-libsecret \
  --enable-features=TouchpadOverscrollHistoryNavigation \
  --load-extension=... \
  --user-data-dir=/tmp/opencode/gemini-profile \
  --remote-debugging-port=9222
```

CDP endpoint: `http://localhost:9222`

**Important:** The current instance was launched WITHOUT `--remote-allow-origins`. The websocket client uses `suppress_origin=True` to bypass the origin check. The `harvest.py launch` command includes `--remote-allow-origins=*` for robustness.

## Profile persistence

`/tmp/opencode/gemini-profile` lives under `/tmp` and is wiped on reboot. For a persistent agent profile, use a path outside `/tmp`:

```
--profile-dir ~/.config/ouroborus/gemini-chromium
```

## Output

- `--out`: full `innerText` of the matching tab after scrolling
- `--chips-out`: source citation JSON from `deep-research-source-lists` selectors
- `--html-out`: full HTML snapshot of the page

Chromium's Gemini "View sources" dialog renders citation chips as empty Angular placeholders; automated extraction returns nothing. Paste chips manually or use Firefox where the dialog works.

## Dependencies

- `websocket-client` (already in `.venv`)
- Chromium with `--remote-debugging-port` and `--remote-allow-origins=*` (or `suppress_origin=True` in the client)
