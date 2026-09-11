#include "home_row_mods.h"
#include "layers.h"
#ifdef OLED_ENABLE
#include "oled_user.h"
#endif

#ifdef RGB_MATRIX_ENABLE
#include "rgb_matrix.h"
#endif

#define LINE_START G(KC_LEFT)
#define LINE_END G(KC_RGHT)
#define WORD_PREV A(KC_LEFT)
#define WORD_NEXT A(KC_RGHT)
#define APP_SWITCH G(KC_TAB)

enum home_row_index {
  HRM_INDEX_A,
  HRM_INDEX_S,
  HRM_INDEX_D,
  HRM_INDEX_F,
  HRM_INDEX_J,
  HRM_INDEX_K,
  HRM_INDEX_L,
  HRM_INDEX_SCLN,
  HRM_INDEX_COUNT,
  HRM_INDEX_NONE = 0xFF
};

static uint8_t pressed_layer[HRM_INDEX_COUNT];

static uint8_t home_row_index(uint16_t keycode) {
  switch (keycode) {
  case HRM_A:
    return HRM_INDEX_A;
  case HRM_S:
    return HRM_INDEX_S;
  case HRM_D:
    return HRM_INDEX_D;
  case HRM_F:
    return HRM_INDEX_F;
  case HRM_J:
    return HRM_INDEX_J;
  case HRM_K:
    return HRM_INDEX_K;
  case HRM_L:
    return HRM_INDEX_L;
  case HRM_SCLN:
    return HRM_INDEX_SCLN;
  default:
    return HRM_INDEX_NONE;
  }
}

static void tap_function_action(uint8_t index) {
  switch (index) {
#ifdef RGB_MATRIX_ENABLE
  case HRM_INDEX_A:
    rgb_matrix_increase_val();
    break;
  case HRM_INDEX_S:
    rgb_matrix_decrease_val();
    break;
#endif
#ifdef CAPS_WORD_ENABLE
  case HRM_INDEX_D:
    caps_word_toggle();
    break;
#endif
#ifdef RGB_MATRIX_ENABLE
  case HRM_INDEX_F:
    rgb_matrix_increase_hue();
    break;
#endif
  default:
    break;
  }
}

static void tap_layer_action(uint8_t layer, uint8_t index) {
  static const uint16_t PROGMEM raise_actions[HRM_INDEX_COUNT] = {
      KC_LPRN, KC_RPRN, KC_LBRC, KC_RBRC, KC_4, KC_5, KC_6, KC_PLUS};
  static const uint16_t PROGMEM nav_actions[HRM_INDEX_COUNT] = {
      LINE_START, LINE_END, WORD_PREV, WORD_NEXT,
      KC_DOWN,    KC_UP,    KC_RGHT,   APP_SWITCH};

  switch (layer) {
  case LAYER_RAISE:
    tap_code16(pgm_read_word(&raise_actions[index]));
    break;
  case LAYER_NAV:
    tap_code16(pgm_read_word(&nav_actions[index]));
    break;
  case LAYER_FUNCTION:
    tap_function_action(index);
    break;
  default:
    break;
  }
}

// Capture the source layer before QMK buffers the tap-hold event.
bool pre_process_record_user(uint16_t keycode, keyrecord_t *record) {
  const uint8_t index = home_row_index(keycode);
  if (index != HRM_INDEX_NONE && record->event.pressed) {
    pressed_layer[index] = get_highest_layer(layer_state | default_layer_state);
  }
  return true;
}

static bool process_layer_home_row_mod(uint16_t keycode, keyrecord_t *record) {
  const uint8_t index = home_row_index(keycode);
  if (index == HRM_INDEX_NONE || record->tap.count == 0) {
    return true;
  }

  if (record->event.pressed) {
    tap_layer_action(pressed_layer[index], index);
  }
  return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef OLED_ENABLE
  oled_record_keypress(keycode, record->event.pressed, record->event.key.row);
#endif
  return process_layer_home_row_mod(keycode, record);
}
