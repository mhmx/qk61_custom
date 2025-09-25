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
    _WIN,                       // [0] Base Windows layer
    _NUM,                       // [1] Numpad layer
    _NAV,                       // [2] Navigation layer
    _FUNC                      // [3] Layer with F-keys, RGB control and media
// The _FUNC layer must be at position [3] for correct connection mode LED indication (BLE, wired, 2.4G)
};

// Tap Dance actions
enum {
    TD_WIN_CAPS = 0,            // Language switch or temporary _NAV layer
    TD_NUM_TAB,                 // Tab modifier: single tap — Tab, double tap — persistent _NUM, hold — temporary _NUM
    TD_NUM_OFF,                 // Turn off persistent _NUM layer
    TD_WIN_LOCK,                // Windows lock or App/Menu key
    TD_CASE                     // for puntoSwitcher - Ctrl+Cmd+Alt to change case of selected text (abc -> ABC)

};

// Shortcut definitions
#define WIN_LANG  A(S(KC_NO))   // Switch Windows language (Alt+Shift)
#define WIN_LOCK  (G(KC_L))     // Lock Windows (Win+L)
#define CTRL_Z    LCTL(KC_Z)    // Ctrl+Z
#define CTRL_X    LCTL(KC_X)    // Ctrl+X
#define CTRL_C    LCTL(KC_C)    // Ctrl+C
#define CTRL_V    LCTL(KC_V)    // Ctrl+V
#define PST_VAL   LALT(KC_1)    // Alt+1 (paste values Excel shortcut)

// --- Tap Dance functions ---

// CapsLock modifier
void td_win_caps_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && !state->pressed) {
        tap_code16(WIN_LANG);   // 1 tap: change language
    } else if (state->count == 2 && !state->pressed) {
        tap_code(KC_CAPS);      // 2 taps: CapsLock
    } else if (state->count == 1 && state->pressed) {
        layer_on(_NAV);         // Hold: activate _NAV on hold
    }
}

void td_win_caps_reset(tap_dance_state_t *state, void *user_data) {
    layer_off(_NAV);
}

// Tab modifier
void td_num_tab_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && !state->pressed) {
        tap_code(KC_TAB);       // 1 tap: Tab
    } else if (state->count == 2 && state->pressed) {
        layer_move(_NUM);       // 2 taps: toggle _NUM
    } else if (state->count == 1 && state->pressed) {
        layer_on(_NUM);         // Hold: activate _NUM on hold
    }
}

void td_num_tab_reset(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        layer_off(_NUM);
    }
}

// Disable Numpad layer
void td_num_layer_off(tap_dance_state_t *state, void *user_data) {
    if ((state->count == 2 && !state->pressed) || (state->count == 1 && state->pressed)) {
        layer_move(_WIN);       // toggle _WIN back on double tap or hold
    } else if (state->count == 1 && !state->pressed) {
        tap_code(KC_TAB);
    }
}

// Windows Lock on hold, App/Menu on tap
void td_winlock_finished(tap_dance_state_t *state, void *user_data) {
    state->pressed ? tap_code16(WIN_LOCK) : tap_code(KC_APP);
}

// puntoSwitcher for win: shortcut Ctrl + Cmd + Alt + \ to change case of selected text (abc -> ABC)
void td_case_finished(tap_dance_state_t *state, void *user_data) {
    if (state->pressed) {
        tap_code(KC_RSFT);
    } else {
        // select word to left
        tap_code16(C(S(KC_LEFT)));

        // delay
        wait_ms(50);
        
        // change case
        tap_code16(C(S(A(KC_BSLS))));
    }
}

// Tap Dance table
tap_dance_action_t tap_dance_actions[] = {
    [TD_WIN_CAPS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_win_caps_finished, td_win_caps_reset),
    [TD_NUM_TAB]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_num_tab_finished,  td_num_tab_reset),
    [TD_NUM_OFF]  = ACTION_TAP_DANCE_FN(td_num_layer_off),
    [TD_WIN_LOCK] = ACTION_TAP_DANCE_FN(td_winlock_finished),
    [TD_CASE] = ACTION_TAP_DANCE_FN(td_case_finished),
};

// --- Combos ---

enum combos {
    COMBO_WIN_E,
    COMBO_ALT_F4,
    COMBO_FN_BASE, // начало F-комбо
    COMBO_LENGTH = COMBO_FN_BASE + 12 // 12 штук — F1–F12
};

const uint16_t PROGMEM win_e_combo[]   = {KC_Q, KC_W, KC_E, COMBO_END};
const uint16_t PROGMEM alt_f4_combo[]  = {KC_W, KC_S, COMBO_END};

// F1–F12: F + 1–0 - = → F1–F12
const uint16_t PROGMEM f_key_combos[][3] = {
    {KC_F, KC_1, COMBO_END},   // F1
    {KC_F, KC_2, COMBO_END},   // F2
    {KC_F, KC_3, COMBO_END},   // F3
    {KC_F, KC_4, COMBO_END},   // F4
    {KC_F, KC_5, COMBO_END},   // F5
    {KC_F, KC_6, COMBO_END},   // F6
    {KC_F, KC_7, COMBO_END},   // F7
    {KC_F, KC_8, COMBO_END},   // F8
    {KC_F, KC_9, COMBO_END},   // F9
    {KC_F, KC_0, COMBO_END},   // F10
    {KC_F, KC_MINS, COMBO_END},// F11
    {KC_F, KC_EQL, COMBO_END}  // F12
    
};

combo_t key_combos[COMBO_LENGTH] = {
    [COMBO_WIN_E] = COMBO_ACTION(win_e_combo),
    [COMBO_ALT_F4] = COMBO_ACTION(alt_f4_combo),
    // F1–F12:
    [COMBO_FN_BASE + 0] = COMBO_ACTION(f_key_combos[0]),
    [COMBO_FN_BASE + 1] = COMBO_ACTION(f_key_combos[1]),
    [COMBO_FN_BASE + 2] = COMBO_ACTION(f_key_combos[2]),
    [COMBO_FN_BASE + 3] = COMBO_ACTION(f_key_combos[3]),
    [COMBO_FN_BASE + 4] = COMBO_ACTION(f_key_combos[4]),
    [COMBO_FN_BASE + 5] = COMBO_ACTION(f_key_combos[5]),
    [COMBO_FN_BASE + 6] = COMBO_ACTION(f_key_combos[6]),
    [COMBO_FN_BASE + 7] = COMBO_ACTION(f_key_combos[7]),
    [COMBO_FN_BASE + 8] = COMBO_ACTION(f_key_combos[8]),
    [COMBO_FN_BASE + 9] = COMBO_ACTION(f_key_combos[9]),
    [COMBO_FN_BASE +10] = COMBO_ACTION(f_key_combos[10]),
    [COMBO_FN_BASE +11] = COMBO_ACTION(f_key_combos[11]),
};

void process_combo_event(uint16_t combo_index, bool pressed) {
    if (!pressed) return;

    switch (combo_index) {
        case COMBO_WIN_E:
            register_code(KC_LGUI);
            tap_code(KC_E);
            unregister_code(KC_LGUI);
            break;
        case COMBO_ALT_F4:
            register_code(KC_LALT);
            tap_code(KC_F4);
            unregister_code(KC_LALT);
            break;
        default:
            // Если это одно из F1–F12
            if (combo_index >= COMBO_FN_BASE && combo_index < COMBO_FN_BASE + 12) {
                tap_code(KC_F1 + (combo_index - COMBO_FN_BASE));
            }
            break;
    }
}

// --- Layers ---
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_WIN] = LAYOUT_tkl_ansi(
        KC_ESC,            KC_1,     KC_2,     KC_3,    KC_4,     KC_5,     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
        TD(TD_NUM_TAB),    KC_Q,     KC_W,     KC_E,    KC_R,     KC_T,     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
        TD(TD_WIN_CAPS),   KC_A,     KC_S,     KC_D,    KC_F,     KC_G,     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
        KC_LSFT,           KC_Z,     KC_X,     KC_C,    KC_V,     KC_B,     KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,                   KC_RSFT,
        KC_LCTL,           KC_LGUI,  KC_LALT,                     KC_SPC,                              KC_RALT, TD(TD_WIN_LOCK),  KC_RCTL, MO(_FUNC)
    ),

    [_NUM] = LAYOUT_tkl_ansi(
        KC_ESC,            _______,  _______,  _______, _______,  _______,  _______, _______, KC_PSLS, KC_PAST, _______, _______, _______, KC_BSPC,
        TD(TD_NUM_OFF),    _______,  _______,  KC_F2,   KC_F4,    _______,  _______, KC_P7,   KC_P8,   KC_P9,   KC_PMNS, _______, _______, _______,
        _______,           _______,  _______,  _______, KC_ENT,   _______,  S(KC_9), KC_P4,   KC_P5,   KC_P6,   KC_PPLS, _______,          KC_PENT,
        _______,           _______,  _______,  _______, _______,  KC_EQL,   S(KC_0), KC_P1,   KC_P2,   KC_P3,   KC_PDOT,                   _______,
        _______,           _______,  _______,                     KC_P0,                              _______,  _______,          _______, _______
    ),

    [_NAV] = LAYOUT_tkl_ansi(
        KC_GRV,            KC_F1,    KC_F2,    KC_F3,   KC_F4,    KC_F5,    KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,
        _______,           _______,  KC_LGUI,  KC_F2,   KC_F4,    _______,  _______, KC_HOME, KC_UP,   KC_PGUP, KC_PSCR, KC_SCRL, KC_NUM,  KC_PAUS,
        _______,           _______,  KC_LCTL,  KC_LSFT, KC_LALT,  KC_ENT,   KC_ENT,  KC_LEFT, KC_DOWN, KC_RGHT, KC_BSPC, KC_DEL,           KC_ENT,
        KC_CAPS,           CTRL_Z,   CTRL_X,   CTRL_C,  CTRL_V,   PST_VAL,  _______, KC_END,  KC_DOT,  KC_PGDN, _______,                   TD(TD_CASE),
        _______,           _______,  _______,                     _______,                             _______, _______,          _______, _______
    ),

    [_FUNC] = LAYOUT_tkl_ansi(
        KC_GRV,            KC_F1,    KC_F2,    KC_F3,   KC_F4,    KC_F5,    KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,
        LOGO_TOG,          MD_BLE1,  MD_BLE2,  MD_BLE3, MD_24G,   _______,  _______, _______, KC_INS,  _______, _______, RGB_SPD, RGB_SPI, U_EE_CLR,
        LOGO_MOD,          LOGO_HUD, LOGO_HUI, _______, _______,  _______,  _______, _______, _______, _______, RGB_HUD, RGB_HUI,          QK_BAT,
        LOGO_VAI,          RGB_VAD,  RGB_VAI,  KC_CALC, _______,  _______,  _______, RGB_RMOD,                  RGB_MOD, KC_MPRV, KC_MNXT, KC_MPLY, 
        LOGO_VAD,          LOGO_SPD, LOGO_SPI,                    RGB_TOG,                             KC_VOLD, KC_VOLU, KC_MUTE,          _______
    )
};
