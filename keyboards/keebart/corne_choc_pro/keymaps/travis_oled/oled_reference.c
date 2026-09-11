#include QMK_KEYBOARD_H
#include "layers.h"
#include "oled_reference.h"

#ifdef OLED_ENABLE

static void write_line(uint8_t row, const char *text) {
    oled_set_cursor(0, row);
    oled_write(text, false);
}

#define TINY_ROWS(a, b, c, d, e) \
    ((uint16_t)(a) | ((uint16_t)(b) << 3) | ((uint16_t)(c) << 6) | \
     ((uint16_t)(d) << 9) | ((uint16_t)(e) << 12))

static uint16_t tiny_glyph(char symbol) {
    switch (symbol) {
        case '~': return TINY_ROWS(0, 2, 5, 0, 0);
        case '!': return TINY_ROWS(2, 2, 2, 0, 2);
        case '@': return TINY_ROWS(7, 5, 7, 4, 7);
        case '#': return TINY_ROWS(5, 7, 5, 7, 5);
        case '$': return TINY_ROWS(2, 7, 6, 3, 7);
        case '%': return TINY_ROWS(5, 1, 2, 4, 5);
        case '`': return TINY_ROWS(4, 2, 0, 0, 0);
        case '(': return TINY_ROWS(2, 4, 4, 4, 2);
        case ')': return TINY_ROWS(2, 1, 1, 1, 2);
        case '[': return TINY_ROWS(6, 4, 4, 4, 6);
        case ']': return TINY_ROWS(3, 1, 1, 1, 3);
        case '\\': return TINY_ROWS(4, 4, 2, 1, 1);
        case '_': return TINY_ROWS(0, 0, 0, 0, 7);
        case '<': return TINY_ROWS(1, 2, 4, 2, 1);
        case '>': return TINY_ROWS(4, 2, 1, 2, 4);
        case '{': return TINY_ROWS(2, 4, 6, 4, 2);
        case '}': return TINY_ROWS(2, 1, 3, 1, 2);
        case '|': return TINY_ROWS(2, 2, 2, 2, 2);
        case '=': return TINY_ROWS(0, 7, 0, 7, 0);
        case '0': return TINY_ROWS(7, 5, 5, 5, 7);
        case '1': return TINY_ROWS(2, 6, 2, 2, 7);
        case '2': return TINY_ROWS(7, 1, 7, 4, 7);
        case '3': return TINY_ROWS(7, 1, 7, 1, 7);
        case '4': return TINY_ROWS(5, 5, 7, 1, 1);
        case '5': return TINY_ROWS(7, 4, 7, 1, 7);
        case '6': return TINY_ROWS(7, 4, 7, 5, 7);
        case '7': return TINY_ROWS(7, 1, 1, 1, 1);
        case '8': return TINY_ROWS(7, 5, 7, 5, 7);
        case '9': return TINY_ROWS(7, 5, 7, 1, 7);
        case '-': return TINY_ROWS(0, 0, 7, 0, 0);
        case '*': return TINY_ROWS(5, 2, 7, 2, 5);
        case '+': return TINY_ROWS(0, 2, 7, 2, 0);
        case '.': return TINY_ROWS(0, 0, 0, 0, 2);
        case '/': return TINY_ROWS(1, 1, 2, 4, 4);
        default: return 0;
    }
}

static void write_tiny_key_row(uint8_t page, const char keys[7]) {
    const uint8_t top = page * 8 + 1;

    for (uint8_t x = 0; x < 32; x++) {
        for (uint8_t y = page * 8; y < page * 8 + 8; y++) {
            oled_write_pixel(x, y, false);
        }
    }

    for (uint8_t key = 0; key < 6; key++) {
        const uint16_t glyph = tiny_glyph(keys[key]);
        const uint8_t left = 1 + key * 5;
        for (uint8_t y = 0; y < 5; y++) {
            for (uint8_t x = 0; x < 3; x++) {
                if (glyph & ((uint16_t)1 << (y * 3 + 2 - x))) {
                    oled_write_pixel(left + x, top + y, true);
                }
            }
        }
    }
}

static void render_raise(bool left) {
    if (left) {
        write_line(0, "RAISE LEFT");
        write_tiny_key_row(2, "~!@#$%");
        write_tiny_key_row(6, "`()[]\\");
        write_tiny_key_row(10, "_<>{}|");
    } else {
        write_line(0, "RAISE RGHT");
        write_tiny_key_row(2, "=789- ");
        write_tiny_key_row(6, "*456+ ");
        write_tiny_key_row(10, "0123./");
    }
}

static void render_nav_left(void) {
    write_line(0, "NAV LEFT");
    write_line(1, "Q  CMD1");
    write_line(2, "W  CMD2");
    write_line(3, "E  CMD3");
    write_line(4, "R  CMD4");
    write_line(5, "T  CMD5");
    write_line(6, "A  LINE<");
    write_line(7, "S  LINE>");
    write_line(8, "D  WORD<");
    write_line(9, "F  WORD>");
    write_line(10, "G  SHOT");
    write_line(11, "Z  UNDO");
    write_line(12, "X  REDO");
    write_line(13, "C  COPY");
    write_line(14, "V  PASTE");
    write_line(15, "B  CUT");
}

static void render_nav_right(void) {
    write_line(0, "NAV RIGHT");
    write_line(1, "Y PREVTAB");
    write_line(2, "U NEXTTAB");
    write_line(3, "I CLOSE");
    write_line(4, "O REOPEN");
    write_line(5, "P WINDOW");
    write_line(6, "H LEFT");
    write_line(7, "J DOWN");
    write_line(8, "K UP");
    write_line(9, "L RIGHT");
    write_line(10, "; APPS");
    write_line(11, "N PLAY");
    write_line(12, "M PREV");
    write_line(13, ", NEXT");
    write_line(14, ". VOL-");
    write_line(15, "/ VOL+");
}

static void render_function(bool left) {
    if (left) {
        write_line(0, "FUNC LEFT");
        write_line(1, "TAB F1");
        write_line(2, "Q   F2");
        write_line(3, "W   F3");
        write_line(4, "E   F4");
        write_line(5, "R   F5");
        write_line(6, "T   F6");
        write_line(8, "CAPS RGB");
        write_line(9, "A BRIGHT+");
        write_line(10, "S BRIGHT-");
        write_line(11, "D CAPSWORD");
        write_line(12, "F COLOR");
        write_line(13, "SHIFT MODE");
        write_line(15, "B BOOT");
    } else {
        write_line(0, "FUNC RIGHT");
        write_line(2, "Y   F7");
        write_line(3, "U   F8");
        write_line(4, "I   F9");
        write_line(5, "O   F10");
        write_line(6, "P   F11");
        write_line(7, "DEL F12");
    }
}

void oled_render_layer_reference(uint8_t layer, bool left) {
    switch (layer) {
        case LAYER_RAISE:
            render_raise(left);
            break;
        case LAYER_NAV:
            if (left) {
                render_nav_left();
            } else {
                render_nav_right();
            }
            break;
        case LAYER_FUNCTION:
            render_function(left);
            break;
        default:
            break;
    }
}

#endif // OLED_ENABLE
