# Keebart Corne Choc Pro configuration

Personal Vial/QMK userspace for the standard Keebart Corne Choc Pro with OLED displays.

Print the one-page keymap: [PDF](docs/corne-choc-pro-keymap.pdf) · [browser version](docs/keymap-print.html)

## Keymap at a glance

`tap/hold` marks dual-role keys. `▽` is transparent, `×` is disabled, and `Lock` keeps the active layer on. A locked layer gains `*` on the OLED and unlocks automatically after 60 seconds idle.

### Base

```text
 Tab       Q       W       E       R       T      Rep | ARep      Y       U       I       O       P      Del
Esc/Nav  A/Ctrl  S/Opt   D/Cmd   F/Shift   G     Opt  | Opt       H     J/Shift K/Cmd   L/Opt   ;/Ctrl    '
 Shift     Z       X       C       V       B               |      N       M       ,       .       /     Function
                    OneCtrl  Enter/Cmd  Tab/Num | Space  Bsp/Nav  OneShift
```

The home-row modifiers are macOS CAGS: `Ctrl`, `Option`, `Command`, `Shift`, mirrored across both hands. Tap the Caps position for Escape or hold it for Navigate. `Rep` repeats the last key; `ARep` performs its natural opposite.

### Raise: symbols + numpad

Hold `Tab/Num`. Programming symbols stay on the left while the right hand becomes a numpad:

```text
  ~       !       @       #       $       %    Lock | Rep      =       7       8       9       -      Bsp
  `       (       )       [       ]     Bslash   ▽  |  ▽       *       4       5       6       +      Enter
  _       <       >       {       }      Pipe       |          0       1       2       3       .       /
                              ▽       ▽     Raise |  ▽       ▽       :
```

The left `Tab/Num` thumb activates an opposite-hand `789/456/123` numpad with operators, Backspace, and Enter around it. Paired delimiters occupy adjacent left-hand keys; colon remains on the right outer thumb for Vim commands.

### Navigate

Hold `Esc/Nav` or `Bsp/Nav`:

```text
  ▽    Cmd1   Cmd2   Cmd3   Cmd4   Cmd5   Lock | Lock PrevTab NextTab Close  Reopen  Window    ▽
  ▽    Line←  Line→  Word←  Word→  PgDn    ▽  |  ▽    Left    Down     Up    Right AppSwitch  ▽
  ▽    Undo   Redo   Copy   Paste   Cut        |      Play    Prev    Next   Vol-    Vol+      ▽
                              ▽       ▽       ▽ |  ▽      Nav      ▽
```

- Physical H/J/K/L become Left/Down/Up/Right.
- Q–T send `Command+1…5`; Y/U send previous/next tab.
- Line motion is `Command+Left/Right`; word motion is `Option+Left/Right`.
- Close, Reopen, Window, and AppSwitch send `Command+W`, `Command+Shift+T`, Command+Backtick, and `Command+Tab`.
- Z/X/C/V/B send Undo, Redo, Copy, Paste, and Cut.

### Function + utilities

Tap Function for one key or hold it while pressing another:

```text
 F1       F2       F3       F4       F5   F6   Boot | ×    F7   F8   F9   F10  F11  F12
RGB Tog  Bright+  Bright-  CapsWord Lock   ×     ×  | ×     ×    ×    ×     ×    ×    ×
RGB Mod     ×        ×        ×       ×    ×        |       ×    ×    ×     ×    ×    ▽
                                  ▽     ▽     ▽ | ▽     ▽     ▽
```

Boot is deliberately moved to the inner extension, away from the Function key. Caps Word makes identifiers such as `API_BASE_URL`; the OLED Caps icon stays lit while it is active.

### Repeat behavior

- `Rep` repeats keys with their modifiers: `=` then Rep produces `==`.
- QMK defaults give `ARep` useful opposites such as J/K, H/L, W/B, arrows, Home/End, Page Up/Down, Backspace/Delete, and matching square or curly brackets.
- The saved Vial profile adds `!` → `=`, `-` → `>`, and `=` → `>`, making `!=`, `->`, and `=>` two-key rolls.
- Raise exposes Lock on the left inner extension and Repeat on the right; Navigate exposes Lock on both sides. Function uses its physical F position.

See the [detailed layout guide](docs/layout.md) for examples, layer behavior, and tap-hold tuning.

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
- The right middle thumb is a second Navigation/Backspace key; Space sits on the stronger inner thumb.
- Raise combines left-hand programming symbols with a right-hand numpad.
- Brackets and braces are direct keys—no additional Shift chord.
- OLEDs show the active Base, Raise, Navigate, or Function layer.
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
