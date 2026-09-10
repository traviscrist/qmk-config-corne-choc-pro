#include QMK_KEYBOARD_H
#include "layers.h"

#define CMD_1 G(KC_1)
#define CMD_2 G(KC_2)
#define CMD_3 G(KC_3)
#define CMD_4 G(KC_4)
#define CMD_5 G(KC_5)
#define TAB_PREV G(S(KC_LBRC))
#define TAB_NEXT G(S(KC_RBRC))
#define CLOSE_TAB G(KC_W)
#define REOPEN_TAB G(S(KC_T))
#define NEXT_WINDOW G(KC_GRV)
#define APP_SWITCH G(KC_TAB)
#define LINE_START G(KC_LEFT)
#define LINE_END G(KC_RGHT)
#define WORD_PREV A(KC_LEFT)
#define WORD_NEXT A(KC_RGHT)
#define UNDO G(KC_Z)
#define REDO G(S(KC_Z))
#define COPY G(KC_C)
#define PASTE G(KC_V)
#define CUT G(KC_X)

// Exempt both layer-tap positions and all thumbs from Chordal Hold's
// same-hand rule. Home-row mod-taps retain strict left/right handedness.
const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM =
    LAYOUT_split_3x6_3_ex2(
        'L', 'L', 'L', 'L', 'L', 'L', 'L',    'R', 'R', 'R', 'R', 'R', 'R', 'R',
        '*', 'L', 'L', 'L', 'L', 'L', 'L',    'R', 'R', 'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L', 'L',                   'R', 'R', 'R', 'R', 'R', 'R',
                            '*', '*', '*',    '*', '*', '*'
    );

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_split_3x6_3_ex2(
        //,---------------------------------------------------------------------.  ,---------------------------------------------------------------------.
             KC_TAB,       KC_Q,       KC_W,       KC_E,       KC_R,       KC_T, QK_REP,    QK_AREP,       KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,  KC_DEL,
        //|--------+------------+------------+------------+------------+------------+--------|  |--------+------------+------------+------------+------------+------------+--------|
            LT(_NAV, KC_ESC), LCTL_T(KC_A), LALT_T(KC_S), LGUI_T(KC_D), LSFT_T(KC_F),       KC_G, KC_LALT,    KC_RALT,       KC_H, RSFT_T(KC_J), RGUI_T(KC_K), RALT_T(KC_L), RCTL_T(KC_SCLN), KC_QUOT,
        //|--------+------------+------------+------------+------------+------------+--------'  `--------+------------+------------+------------+------------+------------+--------|
            KC_LSFT,       KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,                               KC_N,       KC_M,    KC_COMM,     KC_DOT,    KC_SLSH, OSL(_FUNC),
        //|--------+------------+------------+------------+------------+------------+--------.  ,--------+------------+------------+------------+------------+------------+--------|
                                                        OSM(MOD_LCTL), LGUI_T(KC_ENT), LT(_NUM, KC_TAB),    KC_SPC, LT(_NAV, KC_BSPC), OSM(MOD_RSFT)
                                                    //`--------------------------------------'  `--------------------------------------'
    ),

    [_NUM] = LAYOUT_split_3x6_3_ex2(
        //,---------------------------------------------------------------------.  ,---------------------------------------------------------------------.
            KC_TILD, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC, QK_LLCK,    QK_REP, KC_EQL,    KC_7,    KC_8,    KC_9, KC_MINS, KC_BSPC,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
            KC_GRV, KC_LPRN, KC_RPRN, KC_LBRC, KC_RBRC, KC_BSLS, _______,    _______, KC_ASTR,    KC_4,    KC_5,    KC_6, KC_PLUS,  KC_ENT,
        //|--------+--------+--------+--------+--------+--------+--------'  `--------+--------+--------+--------+--------+--------+--------|
            KC_UNDS, KC_LABK, KC_RABK, KC_LCBR, KC_RCBR, KC_PIPE,                         KC_0,    KC_1,    KC_2,    KC_3,  KC_DOT, KC_SLSH,
        //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
                                                _______, _______, _______,    _______, _______, KC_COLN
                                            //`--------------------------'  `--------------------------'
    ),

    [_NAV] = LAYOUT_split_3x6_3_ex2(
        //,---------------------------------------------------------------------.  ,---------------------------------------------------------------------.
            _______,   CMD_1,   CMD_2,   CMD_3,   CMD_4,   CMD_5, QK_LLCK,    QK_LLCK, TAB_PREV, TAB_NEXT, CLOSE_TAB, REOPEN_TAB, NEXT_WINDOW, _______,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
            _______, LINE_START, LINE_END, WORD_PREV, WORD_NEXT, KC_PGDN, _______,    _______, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, APP_SWITCH, _______,
        //|--------+--------+--------+--------+--------+--------+--------'  `--------+--------+--------+--------+--------+--------+--------|
            _______,   UNDO,    REDO,    COPY,   PASTE,     CUT,                      KC_MPLY, KC_MPRV, KC_MNXT, KC_VOLD, KC_VOLU, _______,
        //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
                                                _______, _______, _______,    _______, _______, _______
                                            //`--------------------------'  `--------------------------'
    ),

    [_FUNC] = LAYOUT_split_3x6_3_ex2(
        //,---------------------------------------------------------------------.  ,---------------------------------------------------------------------.
              KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6, QK_BOOT,    XXXXXXX,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
            RGB_TOG, RGB_VAI, RGB_VAD, CW_TOGG, QK_LLCK, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------+--------'  `--------+--------+--------+--------+--------+--------+--------|
            RGB_MOD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
        //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
                                                _______, _______, _______,    _______, _______, _______
                                            //`--------------------------'  `--------------------------'
    )};
