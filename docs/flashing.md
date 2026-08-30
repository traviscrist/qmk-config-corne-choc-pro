# Build and flash

## GitHub

Each push builds the OLED Vial firmware. Download the UF2 from the workflow artifact or generated release.

## Enter the bootloader

Use one method per half:

- Hold the outer top key while connecting USB: Q-side key on the left, P-side key on the right.
- Through the underside holes, hold **BOOT**, tap **RESET**, then release **BOOT**.
- Activate Function and press the bootloader key on the right bottom row.

A removable RP2040 volume appears. Copy the same UF2 to each half separately.

## Apply Vial settings

Firmware keymaps provide the four default layers. Dynamic QMK settings live in keyboard EEPROM, so after flashing:

1. Open a current Vial release.
2. Choose **File → Load saved layout**.
3. Load `vial/corne-choc-pro.vil` from this repository.
4. Confirm **QMK Settings → Tap-Hold** shows Chordal Hold and Permissive Hold enabled, Hold on Other Key Press disabled, Flow Tap 125 ms, tapping term 250 ms, and quick-tap term 100 ms.

Loading the profile also restores the keymap after an EEPROM reset.

## Hardware checks

- Both halves type and show the same active layer.
- OLED labels change between Base, Numbers, Navigate, and Function.
- Each CAGS home-row key types on tap and modifies an opposite-hand key on hold.
- Same-hand rolls such as `asdf`, `jkl`, and `ion` produce letters, not modifiers.
- Caps tap sends Escape; Caps hold plus H/J/K/L sends arrows.
- Navigation Q/W sends Command+1/2; Y/U sends previous/next tab.
- Numbers braces, brackets, colon, backtick, and tilde work without unexpected modifiers.
