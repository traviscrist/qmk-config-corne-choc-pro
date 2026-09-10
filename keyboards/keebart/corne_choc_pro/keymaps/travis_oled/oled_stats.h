#pragma once

#include <stdint.h>

typedef struct {
    uint8_t wpm_25s;
    uint8_t wpm_1m;
    uint8_t wpm_peak_24h;
} oled_wpm_stats_t;

void oled_stats_record_key(uint16_t keycode);
void oled_stats_update(void);
oled_wpm_stats_t oled_stats_snapshot(void);
void oled_render_wpm_footer(oled_wpm_stats_t stats);
