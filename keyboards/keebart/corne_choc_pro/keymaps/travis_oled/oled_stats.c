#include QMK_KEYBOARD_H
#include "oled_stats.h"

#ifdef OLED_ENABLE

#define WPM_SHORT_WINDOW 25
#define WPM_LONG_WINDOW 60
#define WPM_MINUTES_PER_DAY 1440
#define WPM_WORD_SIZE 5

static uint8_t keypress_samples[WPM_LONG_WINDOW] = {0};
static uint8_t minute_peaks[WPM_MINUTES_PER_DAY] = {0};
static uint8_t current_second_presses = 0;
static uint8_t sample_index = 0;
static uint8_t sample_count = 0;
static uint16_t minute_index = 0;
static uint32_t total_samples = 0;
static uint32_t last_sample_ms = 0;
static oled_wpm_stats_t current_stats = {0, 0, 0};

static const uint8_t PROGMEM tiny_digits[10][3] = {
    {0x1F, 0x11, 0x1F}, // 0
    {0x00, 0x1F, 0x00}, // 1
    {0x1D, 0x15, 0x17}, // 2
    {0x15, 0x15, 0x1F}, // 3
    {0x07, 0x04, 0x1F}, // 4
    {0x17, 0x15, 0x1D}, // 5
    {0x1F, 0x15, 0x1D}, // 6
    {0x01, 0x1D, 0x03}, // 7
    {0x1F, 0x15, 0x1F}, // 8
    {0x17, 0x15, 0x1F}  // 9
};

void oled_stats_record_key(uint16_t keycode) {
    if (wpm_keycode(keycode) && current_second_presses < UINT8_MAX) {
        current_second_presses++;
    }
}

static uint8_t calculate_wpm(uint8_t window) {
    const uint8_t seconds = sample_count < window ? sample_count : window;
    if (seconds == 0) {
        return 0;
    }

    uint16_t presses = 0;
    uint8_t index = sample_index;
    for (uint8_t i = 0; i < seconds; i++) {
        index = index == 0 ? WPM_LONG_WINDOW - 1 : index - 1;
        presses += keypress_samples[index];
    }

    const uint32_t denominator = (uint32_t)seconds * WPM_WORD_SIZE;
    const uint32_t rounded_wpm = ((uint32_t)presses * 60 + denominator / 2) /
                                 denominator;
    return rounded_wpm > UINT8_MAX ? UINT8_MAX : rounded_wpm;
}

static void recalculate_peak(void) {
    current_stats.wpm_peak_24h = 0;
    for (uint16_t i = 0; i < WPM_MINUTES_PER_DAY; i++) {
        if (minute_peaks[i] > current_stats.wpm_peak_24h) {
            current_stats.wpm_peak_24h = minute_peaks[i];
        }
    }
}

void oled_stats_update(void) {
    if (timer_elapsed32(last_sample_ms) < 1000) {
        return;
    }
    last_sample_ms = timer_read32();

    if (total_samples > 0 && total_samples % 60 == 0) {
        minute_index = (minute_index + 1) % WPM_MINUTES_PER_DAY;
        const bool peak_expired = minute_peaks[minute_index] ==
                                  current_stats.wpm_peak_24h;
        minute_peaks[minute_index] = 0;
        if (peak_expired) {
            recalculate_peak();
        }
    }

    keypress_samples[sample_index] = current_second_presses;
    current_second_presses = 0;
    sample_index = (sample_index + 1) % WPM_LONG_WINDOW;
    if (sample_count < WPM_LONG_WINDOW) {
        sample_count++;
    }
    total_samples++;

    current_stats.wpm_25s = calculate_wpm(WPM_SHORT_WINDOW);
    current_stats.wpm_1m = calculate_wpm(WPM_LONG_WINDOW);
    if (sample_count >= WPM_SHORT_WINDOW &&
        current_stats.wpm_25s > minute_peaks[minute_index]) {
        minute_peaks[minute_index] = current_stats.wpm_25s;
        if (current_stats.wpm_25s > current_stats.wpm_peak_24h) {
            current_stats.wpm_peak_24h = current_stats.wpm_25s;
        }
    }
}

oled_wpm_stats_t oled_stats_snapshot(void) {
    return current_stats;
}

static uint8_t tiny_number_width(uint8_t value) {
    if (value >= 100) {
        return 11;
    }
    if (value >= 10) {
        return 7;
    }
    return 3;
}

static uint8_t draw_tiny_digit(uint8_t digit, uint8_t x, uint8_t page) {
    for (uint8_t column = 0; column < 3; column++) {
        oled_write_raw_byte(
            pgm_read_byte(&tiny_digits[digit][column]),
            page * OLED_DISPLAY_HEIGHT + x + column
        );
    }
    return x + 4;
}

static uint8_t draw_tiny_number(uint8_t value, uint8_t x, uint8_t page) {
    if (value >= 100) {
        x = draw_tiny_digit(value / 100, x, page);
    }
    if (value >= 10) {
        x = draw_tiny_digit((value / 10) % 10, x, page);
    }
    return draw_tiny_digit(value % 10, x, page) - 1;
}

void oled_render_wpm_footer(oled_wpm_stats_t stats) {
    const uint8_t gap = 3;
    const uint8_t total_width = tiny_number_width(stats.wpm_25s) +
                                tiny_number_width(stats.wpm_1m) +
                                tiny_number_width(stats.wpm_peak_24h) + 2 * gap;
    uint8_t x = (OLED_DISPLAY_HEIGHT - total_width) / 2;

    oled_set_cursor(3, 14);
    oled_write_P(PSTR("WPM"), false);
    for (uint8_t column = 0; column < OLED_DISPLAY_HEIGHT; column++) {
        oled_write_raw_byte(0, 15 * OLED_DISPLAY_HEIGHT + column);
    }
    x = draw_tiny_number(stats.wpm_25s, x, 15) + gap;
    x = draw_tiny_number(stats.wpm_1m, x, 15) + gap;
    draw_tiny_number(stats.wpm_peak_24h, x, 15);
}

#endif // OLED_ENABLE
