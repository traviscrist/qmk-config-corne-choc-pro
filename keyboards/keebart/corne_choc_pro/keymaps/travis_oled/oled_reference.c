#include QMK_KEYBOARD_H
#include "layers.h"
#include "oled_reference.h"

#ifdef OLED_ENABLE

static void write_line(uint8_t row, const char *text) {
    oled_set_cursor(0, row);
    oled_write(text, false);
}

static void render_raise(bool left) {
    if (left) {
        write_line(0, "RAISE LEFT");
        write_line(2, "~!@#$%");
        write_line(4, "`()[]\\");
        write_line(6, "_<>{}|");
        write_line(10, "HOLD TAB");
        write_line(11, "L THUMB");
    } else {
        write_line(0, "RAISE RGHT");
        write_line(2, "=789-SHOT");
        write_line(4, "*456+ENT");
        write_line(6, "0123./");
        write_line(10, "BSP");
        write_line(11, "R INNER");
        write_line(13, "COLON");
        write_line(14, "R OUTER");
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
    write_line(10, "G  PGDN");
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
        case _NUM:
            render_raise(left);
            break;
        case _NAV:
            if (left) {
                render_nav_left();
            } else {
                render_nav_right();
            }
            break;
        case _FUNC:
            render_function(left);
            break;
        default:
            break;
    }
}

#endif // OLED_ENABLE
