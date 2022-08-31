#include QMK_KEYBOARD_H
#include "layer_names.h"
#include "custom_keycodes.h"
#include "tap_dance.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_WIN] = LAYOUT(
        TO(_MAC), TO(_MAC),                KC_GRV,        KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC,           KC_HOME, KC_END,
        PREV_TAB, NEXT_TAB,                KC_TAB,           KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,       KC_INS,  KC_DEL,
        PREV_WINDOW_WIN, NEXT_WINDOW_WIN,  ESC_CTRL,            KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_NUHS, KC_ENT,  KC_UP,   KC_DOWN,
        _______, _______,                  KC_LSFT,KC_NUBS,KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,                   KC_LEFT, KC_RGHT,
                                           KC_LGUI,                                 KC_SPC,                                        TD_LALT_RALT, MO(_FN1)
    ),
    [_MAC] = LAYOUT(
        _______, _______,                  KC_NUBS, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,       _______,   _______,
        _______, _______,                  _______,    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,    _______,   _______,
        PREV_WINDOW_MAC, NEXT_WINDOW_MAC,  _______,      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,   _______,
        PREV_WORKSPACE, NEXT_WORKSPACE,    _______,KC_GRV , _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                 _______,   _______,
                                           _______,                                _______,                                                                 KC_RALT, _______
    ),
    [_FN1] = LAYOUT(
        _______, _______,  _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,        _______,   _______,
        _______, _______,  _______,    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,    _______,   _______,
        _______, _______,  _______,      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,   _______,
        _______, _______,  _______,_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                 _______,   _______,
                           _______,                          MO(_FN2),                                                               _______, _______
    ),
    [_FN2] = LAYOUT(
        _______, _______,  _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,      _______,   _______,
        _______, _______,  _______,    _______, _______, EEP_RST, RESET,   _______, _______, _______, _______, _______, _______, _______, _______, _______,    _______,   _______,
        _______, _______,  _______,      _______, HPT_TOG, DEBUG  , _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,   _______,
        _______, _______,  _______,_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                 _______,   _______,
                           _______,                           _______,                                                               _______, _______
    )
};
