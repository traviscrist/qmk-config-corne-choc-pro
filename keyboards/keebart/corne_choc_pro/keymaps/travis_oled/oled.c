#include QMK_KEYBOARD_H
#include "layers.h"
#include "oled_reference.h"
#include "oled_stats.h"
#include "oled_user.h"

#ifdef OLED_ENABLE
#include "bitmaps.h"
#include "transactions.h"

static const uint16_t SPLASH_DURATION_MS = 2500;

typedef struct {
    bool oled_on;
    oled_wpm_stats_t wpm;
    uint32_t presses_left;
    uint32_t presses_right;
} oled_state_m2s_t;

static bool oled_init_done = false;
static uint8_t oled_max_char = 0;
static bool splash_active = true;
static bool splash_rendered = false;
static uint32_t splash_start_ms = 0;
static uint32_t user_ontime = 0;
static uint32_t presses_left = 0;
static uint32_t presses_right = 0;
static uint8_t rendered_layer = UINT8_MAX;
static oled_state_m2s_t remote_oled_state = {
    false, {0, 0, 0}, 0, 0
};

static oled_state_m2s_t get_local_oled_state(void) {
    oled_state_m2s_t state = {
        is_oled_on(),
        oled_stats_snapshot(),
        presses_left,
        presses_right
    };
    return state;
}

static inline pin_t get_charge_pump_enable_pin(void) {
    return is_keyboard_left() ? GP5 : GP25;
}

static void print_centered(uint8_t row, const char *text) {
    const uint8_t length = strlen(text);
    oled_set_cursor(0, row);
    oled_write_P(PSTR("          "), false);
    oled_set_cursor(length < oled_max_char ? (oled_max_char - length) / 2 : 0, row);
    oled_write(text, false);
}

static uint8_t get_side_percentage(bool left) {
    const uint32_t left_count = is_keyboard_master()
                                    ? presses_left
                                    : remote_oled_state.presses_left;
    const uint32_t right_count = is_keyboard_master()
                                     ? presses_right
                                     : remote_oled_state.presses_right;
    const uint64_t total = (uint64_t)left_count + right_count;
    if (total == 0) {
        return 0;
    }

    const uint64_t side_count = left ? left_count : right_count;
    return (side_count * 100 + total / 2) / total;
}

static void render_splash(void) {
    if (!splash_rendered) {
        oled_clear();
        oled_set_cursor(0, 0);
        oled_write_raw_P(STARTUP_BITMAP, sizeof(STARTUP_BITMAP));
        splash_rendered = true;
    }
}

static void sync_oled_state_slave(uint8_t in_len, const void *in_data,
                                  uint8_t out_len, void *out_data) {
    if (in_len >= sizeof(oled_state_m2s_t)) {
        memcpy(&remote_oled_state, in_data, sizeof(oled_state_m2s_t));
    }
}

void keyboard_post_init_user(void) {
    const pin_t charge_pump_pin = get_charge_pump_enable_pin();
    gpio_set_pin_output(charge_pump_pin);
    gpio_write_pin_low(charge_pump_pin);
    wait_ms(5);

    transaction_register_rpc(USER_SYNC_OLED_STATE, sync_oled_state_slave);
    if (!is_keyboard_master()) {
        wait_ms(90);
    }
}

void housekeeping_task_user(void) {
    if (!is_keyboard_master()) {
        return;
    }

    static uint32_t last_state_sync = 0;
    if (timer_elapsed32(last_state_sync) > 500) {
        const oled_state_m2s_t state = get_local_oled_state();
        (void)transaction_rpc_send(USER_SYNC_OLED_STATE, sizeof(state), &state);
        last_state_sync = timer_read32();
    }
}

void oled_record_keypress(uint16_t keycode, bool pressed, uint8_t row) {
    user_ontime = timer_read32();
    if (pressed && is_keyboard_master()) {
        oled_stats_record_key(keycode);
        if (row < MATRIX_ROWS / 2) {
            presses_left++;
        } else {
            presses_right++;
        }
    }
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_90;
}

bool oled_post_init(void) {
    if (!oled_init_done) {
        oled_max_char = oled_max_chars();

        const pin_t charge_pump_pin = get_charge_pump_enable_pin();
        gpio_write_pin_high(charge_pump_pin);
        wait_ms(20);
        oled_clear();

        splash_start_ms = timer_read32();
        splash_active = true;
        oled_init_done = true;
    }
    return false;
}

static bool oled_should_render(void) {
    if (is_keyboard_master()) {
        const bool timed_out = timer_elapsed32(user_ontime) > OLED_TIMEOUT_USER;
        if (timed_out) {
            if (is_oled_on()) {
                oled_off();
                const oled_state_m2s_t state = get_local_oled_state();
                (void)transaction_rpc_send(USER_SYNC_OLED_STATE, sizeof(state), &state);
            }
            return false;
        }
        if (!is_oled_on()) {
            oled_on();
            const oled_state_m2s_t state = get_local_oled_state();
            (void)transaction_rpc_send(USER_SYNC_OLED_STATE, sizeof(state), &state);
        }
        return true;
    }

    if (remote_oled_state.oled_on) {
        if (!is_oled_on()) {
            oled_on();
        }
        return true;
    }
    if (is_oled_on()) {
        oled_off();
    }
    return false;
}

static void render_base(bool left) {
    char percentage[5];
    snprintf(percentage, sizeof(percentage), "%u%%", get_side_percentage(left));

    print_centered(0, "Base");
    print_centered(6, left ? "Left" : "Right");
    print_centered(8, percentage);

    const oled_wpm_stats_t wpm = is_keyboard_master()
                                     ? oled_stats_snapshot()
                                     : remote_oled_state.wpm;
    oled_render_wpm_footer(wpm);
}

bool oled_task_user(void) {
    oled_post_init();
    if (is_keyboard_master()) {
        oled_stats_update();
    }

    if (splash_active) {
        if (timer_elapsed32(splash_start_ms) <= SPLASH_DURATION_MS) {
            render_splash();
            return false;
        }
        splash_active = false;
        oled_clear();
        user_ontime = timer_read32();
    }

    if (!oled_should_render()) {
        return false;
    }

    const uint8_t current_layer = get_highest_layer(layer_state);
    if (rendered_layer != current_layer) {
        oled_clear();
        rendered_layer = current_layer;
    }

    if (current_layer == LAYER_BASE) {
        render_base(is_keyboard_left());
    } else {
        oled_render_layer_reference(current_layer, is_keyboard_left());
    }
    return false;
}

#endif // OLED_ENABLE
