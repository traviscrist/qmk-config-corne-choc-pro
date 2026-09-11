#pragma once

#include "quantum.h"

// F13-F20 are hidden tap proxies; home_row_mods.c emits each layer's real tap
// action.
#define HRM_A LCTL_T(KC_F13)
#define HRM_S LALT_T(KC_F14)
#define HRM_D LGUI_T(KC_F15)
#define HRM_F LSFT_T(KC_F16)
#define HRM_J RSFT_T(KC_F17)
#define HRM_K RGUI_T(KC_F18)
#define HRM_L RALT_T(KC_F19)
#define HRM_SCLN RCTL_T(KC_F20)
