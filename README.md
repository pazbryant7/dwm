# dwm

My custom build of [dwm](https://dwm.suckless.org/) — the suckless dynamic window manager. Patched, trimmed, and adjusted to fit my workflow. Free to use or fork.

## Patches applied

| Patch | Description |
|-------|-------------|
| **pertag** | Maintains layout, mwfact, and nmaster per tag independently |
| **status2d** | Adds color support in the status bar via inline escape codes |
| **xrdb** | Reads colors from `~/.Xresources` at runtime |
| **signal** | Allows sending signals to dwm to trigger actions from scripts |
| **actualfullscreen** | True fullscreen instead of just hiding the bar |
| **hidevacantstags** | Hides tags with no windows in the bar |
| **tagskipvacant** | Skips empty tags when cycling through them |
| **switchtotag** | Follows a window to its tag when spawning it |
| **resizehere** | Resizes floating windows from their current position |
| **dwindle** | Dwindle/Fibonacci tiling layout |
| **attachbellow** | New windows attach below the current window instead of on top |
| **movestack** | Move windows up and down the stack with keybindings |
| **coolautostart** | Runs autostart programs without blocking dwm startup |
| **unfocused borders** | Applies a distinct border color to unfocused windows |
| **notitle** | Removes the window title from the bar |

## Custom changes

Beyond patches, the build includes several hand-written modifications:

- **Layout fixes** — `setlayout` was broken after `pertag`; the layout rotation behavior has been restored
- **Monocle counter** — the monocle layout displays current and total windows per tag (e.g. `[2/5]`)
- **Floating defaults** — all floating windows are centered on spawn with a specific default width and height
- **Tag-specific bar visibility** — the status bar is hidden by default on tags 1 and 2
- **Cleaned up layouts** — unused layouts removed; the floating (NULL) layout is commented out but kept for reference
- **Reduced tag padding** — tighter spacing in the tag area of the bar
- **Removed dead code** — unused functions and variables cleaned out
- **Custom keybindings** — bindings wired to personal scripts (translation, ffplay floating windows, etc.)
- **Defaults updated** — font, border width, and other options set to personal preferences
- **Formatting** — source code reformatted for readability

## Scripts

| Script | Description |
|--------|-------------|
| **translate** | Opens a floating `st` terminal with a translation tool |
| **ffplay** | Launches `ffplay` in a predefined floating window position |

## Try my full setup

To try this alongside the rest of my environment — status bar, scripts, and all — head to **[pazbryant7/ansible-dots](https://github.com/pazbryant7/ansible-dots)** where a Docker image lets you boot the whole thing without touching your machine.

## Building

```sh
# clone the repo
git clone https://github.com/pazbryant7/dwm && cd dwm

# build and install
sudo make clean install
```

Requires: `libx11`, `libxft`, `libxinerama`, and a running X session.

## Usage

Public and free to use. Take what's useful, adapt it, or use it as a reference for your own build.
