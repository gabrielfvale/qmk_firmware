/* Copyright 2020 MechMerlin
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

enum custom_keycodes {
    C_CEDILLA = SAFE_RANGE,
    A_TILDE,
    O_TILDE,
    TERMINAL,
};

enum tap_dance {
    TD_RSFT_CAPS,
    TD_SLSH_DEL,
};

qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for RShift, twice for Caps Lock
    [TD_RSFT_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_RSFT, KC_CAPS),
    // Tap once for ? /, twice for Del
    [TD_SLSH_DEL] = ACTION_TAP_DANCE_DOUBLE(KC_SLSH, KC_DEL),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case C_CEDILLA:
        if (record->event.pressed) { SEND_STRING(SS_RALT(",")"c"); }
        break;
    case A_TILDE:
        if (record->event.pressed) { SEND_STRING("~a"); }
        break;
    case O_TILDE:
        if (record->event.pressed) { SEND_STRING("~o"); }
        break;
    case TERMINAL:
        if (record->event.pressed) { SEND_STRING(SS_LCTL(SS_LALT("t"))); }
        break;
    }
    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
        MO(2),   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  TD(TD_RSFT_CAPS), KC_UP,   KC_SLSH,
        KC_LCTL, KC_LGUI, KC_LALT,                       KC_SPC,                         KC_RALT, MO(1),   KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [1] = LAYOUT(
        RESET,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  RGB_TOG,
        _______, RGB_HUD, RGB_HUI, RGB_SAD, RGB_SAI, _______, _______, _______, _______, _______, _______, KC_MPRV, KC_MNXT, KC_MPLY,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,        RGB_VAI, KC_DEL,
        _______, _______, _______,                      _______,                         _______, _______, RGB_RMOD, RGB_VAD, RGB_MOD
    ),
    [2] = LAYOUT(
        KC_TILD,   KC_P1,   KC_P2,   KC_P3,   KC_P4,   KC_P5,   KC_P6,   KC_P7,   KC_P8,   KC_P9,   KC_P0,  KC_PDOT,  KC_PEQL,  _______,
        _______,   _______, _______, _______, _______, TERMINAL, _______, _______, _______, O_TILDE, _______, _______, _______, _______,
        _______,   A_TILDE, _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______,
        _______,   _______, _______, C_CEDILLA, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
        _______,   _______, _______,                      _______,                           _______, _______, _______, _______, _______
    ),

};
