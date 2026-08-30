# Keebart Corne Choc Pro configuration

Personal Vial/QMK userspace for the standard Keebart Corne Choc Pro with OLED displays.

## Keymap at a glance

`tap/hold` marks dual-role keys. `▽` is transparent and `×` is disabled.

### Base

```text
 Tab       Q       W       E       R       T     Ctrl | Ctrl      Y       U       I       O       P      Del
Esc/Nav  A/Ctrl  S/Opt   D/Cmd   F/Shift   G     Opt  | Opt       H     J/Shift K/Cmd   L/Opt   ;/Ctrl    '
 Shift     Z       X       C       V       B               |      N       M       ,       .       /     Function
                    OneCtrl  Enter/Cmd  Tab/Num | Bsp/Nav  Space  OneShift
```

The home-row modifiers are macOS CAGS: `Ctrl`, `Option`, `Command`, `Shift`, mirrored across both hands. Tap the Caps position for Escape or hold it for Navigate.

### Numbers

Hold `Tab/Num`:

```text
  ▽       !       @       #       $       %      ▽  |  ▽       ^       &       *       (       )       ▽
  ▽       1       2       3       4       5      ▽  |  ▽       6       7       8       9       0       ▽
  ▽       ×       ~       `       [       {         |          }       ]       ,       .       /       ▽
                              ▽       ▽       Num |  ▽       ▽       :
```

### Navigate

Hold `Esc/Nav` or `Bsp/Nav`:

```text
  ▽    Cmd1   Cmd2   Cmd3   Cmd4   Cmd5    ▽  |  ▽   PrevTab NextTab   ×       \\      |       ▽
  ▽    Home    End     -      =    PgDn    ▽  |  ▽    Left    Down     Up    Right   Menu     ▽
  ▽      <      >    Cmd-C  Cmd-V    ;        |      Play    Prev    Next   Vol-    Vol+     ▽
                              ▽       ▽       ▽ | Nav      ▽       ▽
```

The physical H/J/K/L positions become Left/Down/Up/Right. Q–T send `Command+1…5`; Y/U move between tabs.

### Function

Tap Function for one key or hold it while pressing another:

```text
 F1       F2      F3      F4      F5   F6    × | ×    F7   F8   F9   F10  F11  F12
RGB Tog  Hue+    Sat+    Val+      ×    ×    × | ×     ×    ×    ×     ×    ×    ×
RGB Mod  Hue-    Sat-    Val-      ×    ×      |      ×    ×    ×     ×   Boot   ▽
                              ▽     ▽     ▽ | ▽     ▽     ▽
```

See the [detailed layout guide](docs/layout.md) for shortcuts, layer behavior, and tap-hold tuning.

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
