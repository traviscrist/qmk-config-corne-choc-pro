# Layout

`▽` means transparent. Home-row labels use `tap / hold`.

## Base

```text
 Tab       Q       W       E       R       T     Ctrl | Ctrl      Y       U       I       O       P      Del
Esc/Nav  A/Ctrl  S/Opt   D/Cmd   F/Shift   G     Opt  | Opt       H     J/Shift K/Cmd   L/Opt   ;/Ctrl    '
 Shift     Z       X       C       V       B               |      N       M       ,       .       /     Function
                    OneCtrl  Enter/Cmd  Tab/Num | Bsp/Nav  Space  OneShift
```

The four inner keys remain dedicated modifiers. They are reliable fallbacks for mouse chords and for any shortcut that does not fit the opposite-hand home-row rule.

## Numbers

```text
  ▽       !       @       #       $       %      ▽  |  ▽       ^       &       *       (       )       ▽
  ▽       1       2       3       4       5      ▽  |  ▽       6       7       8       9       0       ▽
  ▽       ×       ~       `       [       {         |          }       ]       ,       .       /       ▽
                              ▽       ▽       Num |  ▽       ▽       :
```

Examples:

- `:q`: hold Numbers, tap the right outer thumb for `:`, release, tap `Q`.
- `{` and `}`: hold Numbers and tap their direct keys. No Shift required.
- `$4`: hold Numbers and tap `$`, then `4`.

## Navigate

The Caps position and right inner thumb both hold this layer.

```text
  ▽    Cmd1   Cmd2   Cmd3   Cmd4   Cmd5    ▽  |  ▽   PrevTab NextTab   ×       \\      |       ▽
  ▽    Home    End     -      =    PgDn    ▽  |  ▽    Left    Down     Up    Right   Menu     ▽
  ▽      <      >    Cmd-C  Cmd-V    ;        |      Play    Prev    Next   Vol-    Vol+     ▽
                              ▽       ▽       ▽ | Nav      ▽       ▽
```

- `Navigate+Q/W/E/R/T` sends `Command+1…5`.
- `Navigate+Y/U` sends `Command+Shift+[` / `Command+Shift+]`.
- Physical H/J/K/L positions are Left/Down/Up/Right.
- Dedicated modifiers remain available through transparency, including Shift/Option plus arrows.

## Function

```text
 F1   F2   F3   F4   F5   F6   × | ×   F7   F8   F9   F10  F11  F12
RGB controls and reserved positions
Bootloader is on the right bottom row, one key in from Function.
```

Tap the Base Function key for one Function-layer key, or hold it while pressing another key.

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
