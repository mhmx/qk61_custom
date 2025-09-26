/* Copyright 2025 CIDOO
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
#include "../../../lib/rdr_lib/rdr_common.h"

// --- Layers and Tap Dance ---

// Layer definitions
enum Layers {
    _MAC,                       // [0] Base macOS layer
    _NUM,                       // [1] Numpad layer
    _NAV,                       // [2] Navigation layer
    _FUNC                       // [3] Layer with F-keys, RGB control and media
// The _FUNC layer must be at position [3] for correct connection mode LED indication (BLE, wired, 2.4G)
};

// Tap Dance actions
enum {
    TD_SWITCH,                  // for puntoSwitcher - Ctrl+Cmd+Backslash to change language of text
    TD_MAC_LOCK,                // macOS or ROption(RAlt)
    TD_CASE                     // for puntoSwitcher - Ctrl+Cmd+Alt to change case of selected text (abc -> ABC)
};

// macOS Lock on hold, RAlt (Option) on tap
void td_maclock_finished(tap_dance_state_t *state, void *user_data) {
    state->pressed ? tap_code16(C(G(KC_Q))) : tap_code(KC_RALT);
}

// puntoSwitcher for macOS: Ctrl + Cmd + Backslash (shortcut in puntoSwitcher), Backslash on hold
void td_switch_finished(tap_dance_state_t *state, void *user_data) {
    state->pressed ? tap_code(KC_BSLS)  : tap_code16(C(G(KC_BSLS)));
}

// puntoSwitcher for macOS: Ctrl + Cmd + Alt to change case of selected text (abc -> ABC)
void td_case_finished(tap_dance_state_t *state, void *user_data) {
    if (state->pressed) {
        tap_code(KC_RSFT);
    } else {
        tap_code16(S(A(KC_LEFT))); // select word to left
        tap_code16(C(G(KC_LALT))); // change case
        wait_ms(250);
        tap_code16(KC_RIGHT);      // unselect word (right)
        tap_code16(KC_SPC);        // add space
    }
}

// Tap Dance table
tap_dance_action_t tap_dance_actions[] = {
    [TD_MAC_LOCK] = ACTION_TAP_DANCE_FN(td_maclock_finished),
    [TD_SWITCH] = ACTION_TAP_DANCE_FN(td_switch_finished),
    [TD_CASE] = ACTION_TAP_DANCE_FN(td_case_finished),
};

// --- Layers ---
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    
    [_MAC] = LAYOUT_tkl_ansi(
        KC_ESC,            KC_1,     KC_2,     KC_3,    KC_4,     KC_5,     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
        LT(_NUM, KC_TAB),  KC_Q,     KC_W,     KC_E,    KC_R,     KC_T,     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
        LT(_NAV,KC_CAPS),  KC_A,     KC_S,     KC_D,    KC_F,     KC_G,     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
        KC_LSFT,           KC_Z,     KC_X,     KC_C,    KC_V,     KC_B,     KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,                   KC_RSFT,
        KC_LCTL,           KC_LALT,  KC_LGUI,                     KC_SPC,                              KC_RGUI, TD(TD_MAC_LOCK),  KC_RCTL, MO(_FUNC)
    ),

    [_NUM] = LAYOUT_tkl_ansi(
        KC_ESC,            _______,  _______,  _______, _______,  _______,  _______, _______, KC_PSLS, KC_PAST, _______, _______, _______, KC_NUM,
        _______,           _______,  _______,  _______, _______,  _______,  _______, KC_P7,   KC_P8,   KC_P9,   KC_PMNS, _______, _______, _______,
        _______,           _______,  _______,  _______, KC_ENT,   _______,  S(KC_9), KC_P4,   KC_P5,   KC_P6,   KC_PPLS, _______,          KC_PENT,
        _______,           _______,  _______,  _______, _______,  KC_PEQL,  S(KC_0), KC_P1,   KC_P2,   KC_P3,   KC_PDOT,                   _______,
        _______,           _______,  _______,                     KC_P0,                               _______, _______,          _______, _______
    ),

    [_NAV] = LAYOUT_tkl_ansi(
        KC_GRV,            KC_F1,    KC_F2,    KC_F3,   KC_F4,    KC_F5,    KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,
        _______,           _______,  KC_LGUI,  KC_F2,   KC_F4,    _______,  _______, KC_HOME, KC_UP,   KC_PGUP, _______, _______, _______, TD(TD_SWITCH),
        _______,           _______,  KC_LCTL,  KC_LSFT, KC_LALT,  KC_ENT,   KC_ENT,  KC_LEFT, KC_DOWN, KC_RGHT, KC_BSPC, KC_DEL,           KC_ENT,
        KC_CAPS,           _______,  _______,  _______, _______,  _______,  _______, KC_END,  _______, KC_PGDN, _______,                   TD(TD_CASE),
        _______,           KC_BRMD,  KC_BRMU,                     _______,                             _______, _______,          _______, _______
    ),

    [_FUNC] = LAYOUT_tkl_ansi(
        KC_GRV,            KC_F1,    KC_F2,    KC_F3,   KC_F4,    KC_F5,    KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,
        LOGO_TOG,          MD_BLE1,  MD_BLE2,  MD_BLE3, MD_24G,   _______,  _______, _______, _______, _______, _______, RGB_SPD, RGB_SPI, U_EE_CLR,
        LOGO_MOD,          LOGO_HUD, LOGO_HUI, _______, _______,  _______,  _______, _______, _______, _______, RGB_HUD, RGB_HUI,          QK_BAT,
        LOGO_VAI,          RGB_VAD,  RGB_VAI,  KC_CALC, _______,  _______,  _______, RGB_RMOD,RGB_MOD, KC_MPRV, KC_MNXT,                   KC_MPLY, 
        LOGO_VAD,          LOGO_SPD, LOGO_SPI,                    RGB_TOG,                             KC_VOLD, KC_VOLU,          KC_MUTE, _______
    )
};
