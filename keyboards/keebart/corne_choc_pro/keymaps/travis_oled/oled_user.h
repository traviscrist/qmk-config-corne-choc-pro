#pragma once

#include <stdbool.h>
#include <stdint.h>

void oled_record_keypress(uint16_t keycode, bool pressed, uint8_t row);
