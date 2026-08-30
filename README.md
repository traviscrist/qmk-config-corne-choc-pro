# Keebart Corne Choc Pro configuration

Personal Vial/QMK userspace for the standard Keebart Corne Choc Pro with OLED displays.

## Firmware

GitHub Actions builds `keebart/corne_choc_pro/standard:travis_oled` against the pinned [`traviscrist/vial-qmk-keebart`](https://github.com/traviscrist/vial-qmk-keebart) firmware revision. Successful pushes publish a UF2 artifact.

1. Open the latest **Build Corne firmware** workflow run or repository release.
2. Download the UF2.
3. Flash the same UF2 to both halves.
4. Open Vial and load [`vial/corne-choc-pro.vil`](vial/corne-choc-pro.vil) to apply the tap-hold settings.

See [flashing](docs/flashing.md) for bootloader details.

## Design

- QWERTY base, optimized for macOS and Vim.
- macOS CAGS home-row mods: `Ctrl Option Command Shift` from pinky to index, mirrored on the right.
- QMK Chordal Hold, Permissive Hold, and Flow Tap reduce false holds during typing rolls.
- Tap the Caps position for Escape; hold it for Navigation.
- The right inner thumb is a second Navigation/Backspace key.
- Numbers and their symbols retain normal horizontal positions.
- Brackets and braces are direct keys—no additional Shift chord.
- OLEDs show the active Base, Numbers, Navigate, or Function layer.
- No `J+K` Escape combo: preserving repeatable Vim `j`/`k` behavior wins over combo novelty.

See [layout](docs/layout.md) for every layer and shortcut.

## macOS laptop parity

The matching MacBook layout lives in `~/.config/kanata/kanata.kbd`, tracked by yadm. Kanata owns home-row mods and the Caps navigation layer on the built-in keyboard. BetterTouchTool remains appropriate for app/window automation, not low-level dual-role keys.

## Local build

From a checkout of `traviscrist/vial-qmk-keebart`:

```sh
qmk config user.overlay_dir="$HOME/travis/qmk-config-corne-choc-pro"
qmk compile -kb keebart/corne_choc_pro/standard -km travis_oled
```
