# Harvest Tools

Reusable scripts for extracting content from live browser sessions. Chromium speaks Chrome DevTools Protocol (CDP); Firefox speaks WebDriver BiDi directly. Both backends are implemented and verified against the live sessions.

## Quick start

**Chromium** (separate profile, debug port 9222):

```sh
python3 .memory/tools/harvest.py launch --browser chromium --port 9222
```

**Firefox** (separate profile, remote agent on port 9223):

```sh
python3 .memory/tools/harvest.py launch --browser firefox --port 9223 --url "https://gemini.google.com/app/new"
```

Log in to Gemini in that window, open your conversation, then harvest:

```sh
.venv/bin/python .memory/tools/harvest.py harvest --browser firefox --port 9223 --out /tmp/output.txt
```

## Output

- `--out`: full `innerText` of the matching tab, after scrolling to load lazy content
- `--chips-out`: source citation JSON from `.deep-research-source-lists` elements
- `--html-out`: full HTML snapshot of the page

## Why a separate profile?

The browser must be started with the debugging flag (`--remote-debugging-port` for both) — you cannot attach to an already-running instance that lacks the flag. A dedicated profile keeps the agent's view scoped to only what you log into there, avoids disrupting your daily browsing, and lets you nuke/relogin without affecting bookmarks or cookies.

To run everything under one profile and give the agent full access to all your tabs, launch your daily browser with the debug flag and point the tool at it via `--port`. The tradeoff: everything reachable on that port is controllable (all tabs, cookies, passwords). On a single-user machine this is your call, but be aware.

## Can two profiles run at the same time?

Yes. Chromium needs a distinct `--user-data-dir` per instance; Firefox needs a distinct `-profile`. Give each its own debug port and both run side by side. A profile directory cannot be shared by two running instances of the same browser.

## Protocol facts (verified against Firefox 155.0.1 / Chromium)

- **Firefox BiDi does NOT use a WebDriver HTTP `/session` endpoint.** Connect the websocket directly to `ws://localhost:PORT/session` and send `session.new` as the first command, with `capabilities.alwaysMatch.browserName = "firefox"`.
- Firefox's `script.evaluate` requires an explicit `awaitPromise` boolean and only accepts `resultOwnership` of `none` or `root` (not `byValue`).
- Firefox `browsingContext.getTree` results omit the `type` field on contexts; match tabs by URL.
- Chromium 9222 survivor: `suppress_origin=True` on the websocket (the instance was launched without `--remote-allow-origins`). The `launch` command adds `--remote-allow-origins=*` for new-profile launches.
- Gemini's live Chromium instance originally launched extra flags: `--ozone-platform=wayland --password-store=gnome-libsecret --enable-features=TouchpadOverscrollHistoryNavigation --load-extension=...`.

## Profile persistence

The default profiles live under `/tmp` and are wiped on reboot:

```
/tmp/opencode/gemini-profile    # chromium
/tmp/opencode/gemini-firefox    # firefox
```

For a persistent agent profile, pass an explicit path outside `/tmp`:

```sh
--profile-dir ~/.config/ouroborus/gemini-firefox
```

Important: to attach BiDi/CDP you must START the browser with `--remote-debugging-port`. Firefox also needs `-profile` (a named profile or a directory). Relaunching your daily Firefox this way reuses its profile while exposing it; prefer the separate throwaway profile and log in fresh.

## Chromium source-chip caveat

Chromium's Gemini "View sources" dialog renders citation chips as empty Angular placeholders; automated extraction returns nothing. Paste chips manually or use Firefox, whose source lists are DOM-text reachable and extracted into `--chips-out`.

## Dependencies

- `websocket-client` (already in `.venv`)
- Chromium with `--remote-debugging-port` and `--remote-allow-origins=*` (or `suppress_origin=True` in the client)
- Firefox with `--remote-debugging-port` (WebDriver BiDi is built into Firefox 155+; no geckodriver, no selenium needed)