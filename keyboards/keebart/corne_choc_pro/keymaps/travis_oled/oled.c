#include QMK_KEYBOARD_H
#include "layers.h"
#include "oled_reference.h"
#include "oled_stats.h"

#ifdef OLED_ENABLE
#include "bitmaps.h"
#include "transactions.h"

static const uint8_t OLED_WIDTH = OLED_DISPLAY_HEIGHT;
static const uint16_t SPLASH_DURATION_MS = 2500;

static const char PROGMEM QMK_LOGO_1[] = {
    0x81, 0x82, 0x83, 0x84, 0x00
};
static const char PROGMEM QMK_LOGO_2[] = {
    0xA1, 0xA2, 0xA3, 0xA4, 0x00
};
static const char PROGMEM QMK_LOGO_3[] = {
    0xC1, 0xC2, 0xC3, 0xC4, 0x00
};

typedef struct {
    bool oled_on;
    bool caps_word_on;
    oled_wpm_stats_t wpm;
} oled_state_m2s_t;

typedef struct {
    uint16_t keycode;
} lastkey_m2s_t;

static bool g_oled_init_done = false;
static uint8_t g_oled_max_char;
static bool g_splash_active = true;
static bool g_splash_rendered = false;
static uint32_t g_splash_start_ms = 0;
static uint32_t g_user_ontime = 0;
static uint16_t g_last_keycode = KC_NO;
static bool g_key_data_dirty = false;
static uint8_t g_rendered_layer = UINT8_MAX;
static oled_state_m2s_t g_remote_oled_state = {
    false, false, {0, 0, 0}
};

static oled_state_m2s_t get_local_oled_state(void) {
    oled_state_m2s_t state = {
        is_oled_on(),
        is_caps_word_on(),
        oled_stats_snapshot()
    };
    return state;
}

static inline pin_t get_charge_pump_enable_pin(void) {
    if (is_keyboard_left()) {
        return GP5;
    } else {
        return GP25;
    }
}

void oled_blit_16x16_P(const char *icon, uint8_t x, uint8_t page) {
    for (uint8_t i = 0; i < 16; i++) {
        char top = pgm_read_byte(&icon[i]);         // column i, top 8 pixels
        char bot = pgm_read_byte(&icon[16 + i]);    // column i, bottom 8 pixels

        oled_write_raw_byte(top, page       * OLED_WIDTH + x + i);
        oled_write_raw_byte(bot, (page + 1) * OLED_WIDTH + x + i);
    }
}

void oled_blit_24x24_P(const char *icon, uint8_t x, uint8_t page) {
    for (uint8_t i = 0; i < 24; i++) {
        char top = pgm_read_byte(&icon[i]);         // column i, top 8 pixels
        char mid = pgm_read_byte(&icon[24 + i]);    // column i, middle 8 pixels
        char bot = pgm_read_byte(&icon[48 + i]);    // column i, bottom 8 pixels

        oled_write_raw_byte(top, page       * OLED_WIDTH + x + i);
        oled_write_raw_byte(mid, (page + 1) * OLED_WIDTH + x + i);
        oled_write_raw_byte(bot, (page + 2) * OLED_WIDTH + x + i);
    }
}

uint16_t unwrap_keycode(uint16_t kc) {
    if (kc >= QK_MOD_TAP && kc <= QK_MOD_TAP_MAX) {
        return QK_MOD_TAP_GET_TAP_KEYCODE(kc);
    }
    if (kc >= QK_LAYER_TAP && kc <= QK_LAYER_TAP_MAX) {
        return QK_LAYER_TAP_GET_TAP_KEYCODE(kc);
    }
    return kc;
}

void oled_print_right_aligned(const char *text, const uint8_t width) {
    uint8_t len = strlen(text);
    uint8_t pad = (len < width) ? (width - len) : 0;
    for (uint8_t i = 0; i < pad; i++) {
        oled_write_P(PSTR(" "), false);
    }
    oled_write(text, false);
}

void print_current_layer(uint8_t row) {
    char layer_str[10];
    const uint8_t current_layer = get_highest_layer(layer_state);
    switch (current_layer) {
        case _BASE:
            strcpy(layer_str, "Base");
            break;
        case _NUM:
            strcpy(layer_str, "Raise");
            break;
        case _NAV:
            strcpy(layer_str, "Navigate");
            break;
        case _FUNC:
            strcpy(layer_str, "Function");
            break;
        default:
            // TODO: consider remove snprintf
            snprintf(layer_str, sizeof(layer_str), "%d", current_layer);
    }

    oled_set_cursor(0, row);
    oled_print_right_aligned(layer_str, g_oled_max_char);
}

void print_uptime(uint8_t row) {
    uint32_t time_ms = timer_read32();
    uint32_t total_min = time_ms / 60000u;
    uint32_t hours = total_min / 60u;
    uint32_t minutes = total_min % 60u;
    if (hours > 999u) {
        hours = 999u;
        minutes = 59u;
    }

    // TODO: consider remove snprintf
    char buf[8];
    snprintf(buf, sizeof(buf), "%3luh%02lum", hours, minutes);
    oled_set_cursor(0, row);
    oled_print_right_aligned(buf, g_oled_max_char);
}

void render_splash(void) {
    if (g_splash_rendered) {
        return;
    }
    oled_clear();
    oled_set_cursor(0, 0);
    oled_write_raw_P(STARTUP_BITMAP, sizeof(STARTUP_BITMAP));
    g_splash_rendered = true;
}

static void user_sync_oled_state_slave(uint8_t in_len, const void* in_data,
                                       uint8_t out_len, void* out_data) {
    if (in_len >= sizeof(oled_state_m2s_t)) {
        memcpy(&g_remote_oled_state, in_data, sizeof(oled_state_m2s_t));
    }
}

static void user_sync_lastkey_slave(uint8_t in_len, const void* in_data,
                                    uint8_t out_len, void* out_data) {
    if (in_len >= sizeof(lastkey_m2s_t)) {
        lastkey_m2s_t packet;
        memcpy(&packet, in_data, sizeof(packet));
        g_last_keycode = packet.keycode;
    }
}

void keyboard_post_init_user(void) {
    pin_t dsp_pen_pin = get_charge_pump_enable_pin();
    gpio_set_pin_output(dsp_pen_pin);
    gpio_write_pin_low(dsp_pen_pin);
    wait_ms(5);

    transaction_register_rpc(USER_SYNC_OLED_STATE, user_sync_oled_state_slave);
    transaction_register_rpc(USER_SYNC_LASTKEY, user_sync_lastkey_slave);

    if (!is_keyboard_master()) {
        wait_ms(90); // wait for master to be ready
    }
}

void housekeeping_task_user(void) {
    if (is_keyboard_master()) {
        static uint32_t last_state_sync = 0;
        static uint32_t last_key_sync = 0;

        if (timer_elapsed32(last_state_sync) > 500) {
            oled_state_m2s_t oled_state_pkt = get_local_oled_state();
            (void)transaction_rpc_send(
                USER_SYNC_OLED_STATE, sizeof(oled_state_pkt), &oled_state_pkt
            );
            last_state_sync = timer_read32();
        }

        if (g_key_data_dirty && timer_elapsed32(last_key_sync) > 50) {
            lastkey_m2s_t keycode_pkt = { g_last_keycode };
            g_key_data_dirty = !transaction_rpc_send(
                USER_SYNC_LASTKEY, sizeof(keycode_pkt), &keycode_pkt
            );
            last_key_sync = timer_read32();
        }
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    g_user_ontime = timer_read32();

    if (record->event.pressed) {
        g_last_keycode = keycode;
        if (is_keyboard_master()) {
            oled_stats_record_key(keycode);
            g_key_data_dirty = true;
        }
    }
    return true;
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_90;
}

bool oled_post_init(void) {
    if (!g_oled_init_done) {
        // set OLED size for characters
        g_oled_max_char = oled_max_chars();

        // enable charge pump
        pin_t dsp_pen_pin = get_charge_pump_enable_pin();
        gpio_write_pin_high(dsp_pen_pin);
        wait_ms(20);
        oled_clear();

        // start timer for splash screen
        g_splash_start_ms = timer_read32();
        g_splash_active = true;

        g_oled_init_done = true;
    }
    return false;
}

bool oled_task_user(void) {
    // perform custom initialisation once
    oled_post_init();

    if (is_keyboard_master()) {
        oled_stats_update();
    }

    // render splash screen
    if (g_splash_active) {
        if (timer_elapsed32(g_splash_start_ms) > SPLASH_DURATION_MS) {
            g_splash_active = false;
            oled_clear();
            g_user_ontime = timer_read32();
        } else {
            render_splash();
        }
        return false;
    }

    // manage oled on/off state based on idle time
    if (is_keyboard_master()) {
        const uint32_t idle_time = timer_elapsed32(g_user_ontime);
        if (!is_oled_on()) {
            if (idle_time > OLED_TIMEOUT_USER) {
                return false; // stay off
            } else {
                oled_on();
                oled_state_m2s_t oled_state_pkt = get_local_oled_state();
                (void)transaction_rpc_send(
                    USER_SYNC_OLED_STATE, sizeof(oled_state_pkt), &oled_state_pkt
                );
            }
        } else {
            if (idle_time > OLED_TIMEOUT_USER) {
                oled_off();
                oled_state_m2s_t oled_state_pkt = get_local_oled_state();
                (void)transaction_rpc_send(
                    USER_SYNC_OLED_STATE, sizeof(oled_state_pkt), &oled_state_pkt
                );
                return false;
            } else {
                // stay on
            }
        }
    } else {
        if (g_remote_oled_state.oled_on) {
            if (!is_oled_on()) {
                oled_on();
            } else {
                // stay on
            }
        } else {
            if (is_oled_on()) {
                oled_off();
                return false;
            } else {
                return false;
                // stay off
            }
        }
    }

    const uint8_t current_layer = get_highest_layer(layer_state);
    if (g_rendered_layer != current_layer) {
        oled_clear();
        g_rendered_layer = current_layer;
    }

    if (current_layer != _BASE) {
        oled_render_layer_reference(current_layer, is_keyboard_left());
        return false;
    }

    if (is_keyboard_left()) {
        oled_set_cursor(0, 0);
        oled_write_P(PSTR("Layer:"), false);
        print_current_layer(1);

        led_t led_state = host_keyboard_led_state();
        oled_blit_16x16_P(
            led_state.num_lock ? NUM_LOCK_BITMAP : EMPTY_BITMAP, 0, 3
        );
        const bool caps_word_on = is_keyboard_master()
                                      ? is_caps_word_on()
                                      : g_remote_oled_state.caps_word_on;
        oled_blit_16x16_P(
            led_state.caps_lock || caps_word_on ? CAPS_LOCK_BITMAP : EMPTY_BITMAP,
            24, 3
        );
        oled_blit_16x16_P(
            led_state.scroll_lock ? SCROLL_LOCK_BITMAP : EMPTY_BITMAP, 48, 3
        );

        oled_set_cursor(0, 8);
        oled_write_P(PSTR("Last Key:"), false);
        oled_set_cursor(0, 9);
        const char *keycode_str = get_keycode_string(unwrap_keycode(g_last_keycode));
        oled_print_right_aligned(keycode_str, g_oled_max_char);

        oled_set_cursor(0, 13);
        oled_write_P(QMK_LOGO_1, false);
        oled_set_cursor(0, 14);
        oled_write_P(QMK_LOGO_2, false);
        oled_set_cursor(0, 15);
        oled_write_P(QMK_LOGO_3, false);
        oled_set_cursor(7, 15);
        oled_write_P(PSTR("QMK"), false);
    } else {
        oled_set_cursor(0, 0);
        oled_write_P(PSTR("Uptime:"), false);
        print_uptime(1);

        oled_blit_24x24_P(KEEBART_BITMAP_24x24, 20, 6);
        oled_set_cursor(2, 10);
        oled_write_P(PSTR("KEEBART"), false);

        const oled_wpm_stats_t wpm = is_keyboard_master()
                                         ? oled_stats_snapshot()
                                         : g_remote_oled_state.wpm;
        oled_render_wpm_footer(wpm);
    }
    return false;
}

#endif // OLED_ENABLE
