VIA_ENABLE = yes
VIAL_ENABLE = yes
VIALRGB_ENABLE = yes
CAPS_WORD_ENABLE = yes
OLED_ENABLE = yes
OLED_DRIVER = ssd1306
OLED_TRANSPORT = i2c
WPM_ENABLE = yes
KEYCODE_STRING_ENABLE = yes

SRC += oled.c oled_reference.c oled_stats.c
