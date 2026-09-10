# Layout

`▽` means transparent, `×` means disabled, and `tap/hold` marks a dual-role key. `Rep` is Repeat, `ARep` is Alternate Repeat, and `Lock` toggles Layer Lock.

## Base

```text
 Tab       Q       W       E       R       T      Rep | ARep      Y       U       I       O       P      Del
Esc/Nav  A/Ctrl  S/Opt   D/Cmd   F/Shift   G     Opt  | Opt       H     J/Shift K/Cmd   L/Opt   ;/Ctrl    '
 Shift     Z       X       C       V       B               |      N       M       ,       .       /     Function
                    OneCtrl  Enter/Cmd  Tab/Num | Space  Bsp/Nav  OneShift
```

The mirrored home-row mods are macOS CAGS:

| Key | Tap | Hold |
| --- | --- | --- |
| A / ; | letter | Control |
| S / L | letter | Option |
| D / K | letter | Command |
| F / J | letter | Shift |

Use the modifier on the hand opposite the shortcut key. For example, hold K for Command while tapping C, V, X, or Z with the left hand. Chordal Hold keeps same-hand typing rolls literal.

The upper inner extension keys are persistent Repeat and Alternate Repeat. The lower inner extensions remain dedicated Option fallbacks; the left and right outer thumbs provide one-shot Control and Shift.

## Raise: symbols + numpad

Hold `Tab/Num`:

```text
  ~       !       @       #       $       %    Lock | Rep      =       7       8       9       -      Bsp
  `       (       )       [       ]     Bslash   ▽  |  ▽       *       4       5       6       +      Enter
  _       <       >       {       }      Pipe       |          0       1       2       3       .       /
                              ▽       ▽     Raise |  ▽       ▽       :
```

Design:

- The left `Tab/Num` thumb activates an opposite-hand numpad.
- Digits use the familiar `789/456/123` shape, with zero beside the bottom row.
- `= - * + . /`, Backspace, and Enter surround the number block.
- `()`, `[]`, `{}`, and `<>` are adjacent left-hand delimiter pairs.
- `\` and `|` share one physical column, while `_`, backtick, tilde, and common shifted-number symbols remain direct.
- Colon remains on the right outer thumb for Vim command mode.
- Lock is on the left inner extension; Repeat is on the right inner extension.

Examples:

- `:q`: hold Raise, tap the right outer thumb for `:`, release, tap Q.
- `API_BASE_URL`: activate Caps Word, then use Raise's direct underscore key as needed.
- `!=`, `->`, `=>`: type the first character, then Alternate Repeat from Base.
- `123.45`: hold Raise and roll across the right-hand numpad.
- Long numeric entry: hold Raise, tap Lock, and release the thumb.

## Navigate

Hold the Caps-position `Esc/Nav` key or the right middle `Bsp/Nav` thumb:

```text
  ▽    Cmd1   Cmd2   Cmd3   Cmd4   Cmd5   Lock | Lock PrevTab NextTab Close  Reopen  Window    ▽
  ▽    Line←  Line→  Word←  Word→  PgDn    ▽  |  ▽    Left    Down     Up    Right AppSwitch  ▽
  ▽    Undo   Redo   Copy   Paste   Cut        |      Play    Prev    Next   Vol-    Vol+      ▽
                              ▽       ▽       ▽ |  ▽      Nav      ▽
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
| Undo / Redo | Command+Z / Command+Shift+Z |
| Copy / Paste / Cut | Command+C / Command+V / Command+X |

Physical H/J/K/L remain literal on Base for Vim and become Left/Down/Up/Right only on Navigate.

## Function + utilities

Tap Function for one Function-layer key or hold it while pressing another:

```text
 F1       F2       F3       F4       F5   F6   Boot | ×    F7   F8   F9   F10  F11  F12
RGB Tog  Bright+  Bright-  CapsWord Lock   ×     ×  | ×     ×    ×    ×     ×    ×    ×
RGB Mod     ×        ×        ×       ×    ×        |       ×    ×    ×     ×    ×    ▽
                                  ▽     ▽     ▽ | ▽     ▽     ▽
```

- Function+D toggles Caps Word for constants and environment variables.
- Function+F locks Function for repeated F-key use.
- Boot is on the upper inner extension, physically separated from the Function activation key.
- RGB is intentionally limited to toggle, brightness up/down, and mode.

## Repeat and Alternate Repeat

Repeat resends the last eligible key with its modifiers. Examples: `=` then Repeat produces `==`; Command+Z then Repeat performs another undo.

Alternate Repeat uses QMK's built-in opposite pairs, including:

- J / K and H / L
- W / B
- Left / Right and Up / Down
- Home / End and Page Up / Page Down
- Backspace / Delete
- matching square and curly brackets

The saved Vial profile adds three unidirectional pairs:

| First key | Alternate Repeat | Result |
| --- | --- | --- |
| `!` | `=` | `!=` |
| `-` | `>` | `->` |
| `=` | `>` | `=>` |

These custom pairs live in Vial's dynamic Alternate Repeat table, so load [`vial/corne-choc-pro.vil`](../vial/corne-choc-pro.vil) after flashing.

## Layer Lock

While holding Raise, tap the left inner `Lock` key; while holding Navigate, tap either inner Lock. Release the layer key and the layer remains active until Lock is tapped again or the 60-second idle timeout expires. Function has Lock on its physical F position.

The OLED adds `*` to a locked layer name, for example `Raise*`. Caps Word reuses the OLED Caps icon so its state is visible without enabling host Caps Lock.

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

The Kanata layout uses the same CAGS home-row mods, Caps/Escape behavior, and Navigate positions on the Apple internal keyboard. Its full number and function rows remain native, so the Corne-only Raise/numpad, Repeat, Layer Lock, RGB, and bootloader controls are not mirrored.
