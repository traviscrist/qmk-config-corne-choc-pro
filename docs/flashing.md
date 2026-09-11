# Build and flash

## GitHub

Each push builds the OLED Vial firmware. Download the UF2 from the workflow artifact or generated release.

## Enter the bootloader

Flash one half at a time over USB; the cable between halves is not required. Disconnect USB power before connecting or disconnecting that cable, and do not power both halves over USB simultaneously.

Use one method per half:

- Hold the physical **Q** key on the left half or **P** key on the right half while connecting that half directly by USB. These are beside Tab and Delete—not the outermost keys.
- Through the underside holes, hold **BOOT**, tap **RESET**, then release **BOOT**.
- Activate Function and press physical **B**.

A removable RP2040 volume appears. Copy the same UF2 to each half separately, then reconnect the halves while USB is disconnected.

## Apply Vial settings

Firmware keymaps provide the four default layers. Dynamic QMK settings live in keyboard EEPROM, so after flashing:

1. Open a current Vial release.
2. Choose **File → Load saved layout**.
3. Load `vial/corne-choc-pro.vil` from this repository.
4. Confirm **QMK Settings → Tap-Hold** shows Chordal Hold and Permissive Hold enabled, Hold on Other Key Press disabled, Flow Tap 125 ms, tapping term 250 ms, and quick-tap term 100 ms.

Loading the profile also restores the keymap after an EEPROM reset.

## Hardware checks

- Both halves type and show Base status after startup.
- Raise, Navigate, and Function replace both OLED screens with per-hand references.
- Each CAGS home-row key types on tap and modifies an opposite-hand key on hold.
- On Raise, Navigate, and Function, tapping every CAGS position keeps its documented layer action while holding it produces the same Base modifier.
- Thumb taps send Tab, Enter, Space, and Backspace; holding Enter activates Raise, holding Space activates Navigate, and holding Backspace repeats it.
- Same-hand rolls such as `asdf`, `jkl`, and `ion` produce letters, not modifiers.
- Caps tap sends Escape; Caps hold plus H/J/K/L sends arrows.
- Navigation Q/W sends Command+1/2; Y/U sends previous/next tab.
- Raise produces `789/456/123`, zero, decimal point, operators, Backspace, and Enter from the documented right-hand positions.
- Raise's parentheses, brackets, braces, angle brackets, pipe, backslash, underscore, colon, backtick, and tilde work without unexpected modifiers.
- Both Base OLEDs show `WPM` above the 25-second average, one-minute average, and powered-session 24-hour peak; the middle percentages match each half's keypress share.
- Function+D toggles Caps Word and the OLED Caps icon follows its state.
- Navigation line/word movement, Screenshot, Undo/Redo/Copy/Paste/Cut, Close/Reopen, app switching, and window switching send the documented macOS shortcuts.
- Function+F advances the RGB hue.
