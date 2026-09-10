# Layout

`▽` means transparent, `×` means disabled, and `tap/hold` marks a dual-role key.

## Base

```text
 Tab       Q       W       E       R       T | Y       U       I       O       P      Del
Esc/Nav  A/Ctrl  S/Opt   D/Cmd   F/Shift   G | H     J/Shift K/Cmd   L/Opt   ;/Ctrl    '
 Shift     Z       X       C       V       B | N       M       ,       .       /     Function
                    OneCtrl  Enter/Cmd  Tab/Num | Bsp/Nav  Space  OneShift
```

The mirrored home-row mods are macOS CAGS:

| Key | Tap | Hold |
| --- | --- | --- |
| A / ; | letter | Control |
| S / L | letter | Option |
| D / K | letter | Command |
| F / J | letter | Shift |

Use the modifier on the hand opposite the shortcut key. For example, hold K for Command while tapping C, V, X, or Z with the left hand. Chordal Hold keeps same-hand typing rolls literal.

The left and right outer thumbs provide one-shot Control and Shift.

## Raise: symbols + numpad

Hold `Tab/Num`:

```text
  ~       !       @       #       $       % | =       7       8       9       -      Bsp
  `       (       )       [       ]     Bslash | *       4       5       6       +      Enter
  _       <       >       {       }      Pipe | 0       1       2       3       .       /
                              ▽       ▽     Raise |  ▽       ▽       :
```

Design:

- The left `Tab/Num` thumb activates an opposite-hand numpad.
- Digits use the familiar `789/456/123` shape, with zero beside the bottom row.
- `= - * + . /`, Backspace, and Enter surround the number block.
- `()`, `[]`, `{}`, and `<>` are adjacent left-hand delimiter pairs.
- `\` and `|` share one physical column, while `_`, backtick, tilde, and common shifted-number symbols remain direct.
- Colon remains on the right outer thumb for Vim command mode.

Examples:

- `:q`: hold Raise, tap the right outer thumb for `:`, release, tap Q.
- `API_BASE_URL`: activate Caps Word, then use Raise's direct underscore key as needed.
- `123.45`: hold Raise and roll across the right-hand numpad.

## Navigate

Hold the Caps-position `Esc/Nav` key or the right inner `Bsp/Nav` thumb:

```text
  ▽    Cmd1   Cmd2   Cmd3   Cmd4   Cmd5 | PrevTab NextTab Close  Reopen  Window    ▽
  ▽    Line←  Line→  Word←  Word→  Shot | Left    Down     Up    Right AppSwitch  ▽
  ▽    Undo   Redo   Copy   Paste   Cut | Play    Prev    Next   Vol-    Vol+      ▽
                              ▽       ▽       ▽ | Nav      ▽       ▽
```

macOS actions:

| Label | Output |
| --- | --- |
| Cmd1…Cmd5 | Command+1…5 |
| PrevTab / NextTab | Command+Shift+[ / Command+Shift+] |
| Close | Command+W |
| Reopen | Command+Shift+T |
| Window | Command+Backtick |
| AppSwitch | Command+Tab |
| Line← / Line→ | Command+Left / Command+Right |
| Word← / Word→ | Option+Left / Option+Right |
| Shot | Command+Shift+4 |
| Undo / Redo | Command+Z / Command+Shift+Z |
| Copy / Paste / Cut | Command+C / Command+V / Command+X |

Physical H/J/K/L remain literal on Base for Vim and become Left/Down/Up/Right only on Navigate.

## Function + utilities

Tap Function for one Function-layer key or hold it while pressing another:

```text
 F1       F2       F3       F4       F5   F6 | F7   F8   F9   F10  F11  F12
RGB Tog  Bright+  Bright-  CapsWord Color  × | ×    ×    ×    ×     ×    ×
RGB Mod     ×        ×        ×       ×  Boot | ×    ×    ×    ×     ×    ▽
                                  ▽     ▽     ▽ | ▽     ▽     ▽
```

- Tap the far-right Function key, then tap the listed control; Function is one-shot and does not need to be held.
- Function+D toggles Caps Word for constants and environment variables.
- Function+F advances the RGB hue; repeat until the desired color appears.
- Function+B enters the bootloader, physically separated from the Function activation key.
- Function+Caps toggles RGB, Function+A/S changes brightness, and Function+left Shift cycles effects.
- Fresh or reset RGB settings start in solid green. RGB changes are saved by QMK.

## OLED displays

On Base, both OLEDs center `Base` at the top. The middle shows `Left` or `Right` with that half's keypress percentage since power-on beneath it. At the bottom, a small `WPM` label sits above the same three unlabeled values on both screens, in this order:

1. rolling 25-second average
2. rolling one-minute average
3. peak rolling 25-second average from the last 24 powered-on hours

The rolling history resets when the keyboard loses power and does not write to flash. On Raise, Navigate, and Function, both displays switch to per-hand references for the keys on their respective halves. Raise uses compact glyphs so each six-key physical row appears on one OLED line.

## Tap-hold defaults

The saved Vial profile applies:

- tapping term: 250 ms
- quick-tap term: 100 ms
- Permissive Hold: enabled
- Hold on Other Key Press: disabled
- Chordal Hold: enabled
- Flow Tap: 125 ms
- one-shot timeout: 2000 ms
- one-shot lock: three taps

Tune Flow Tap first in 25 ms steps. Lower it when a modifier immediately after typing becomes a letter; raise it when quick typing still creates false modifiers.

## MacBook parity

The Kanata layout uses the same CAGS home-row mods, Caps/Escape behavior, and Navigate positions on the Apple internal keyboard. Its full number and function rows remain native, so the Corne-only Raise/numpad, screenshot key, RGB, and bootloader controls are not mirrored.
