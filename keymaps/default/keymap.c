/* Copyright (C) 2023 jonylee@hfd
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

// clang-format off

/*
 * Keymap derived from the "mysetup" VIA configuration stored in
 * mk47.layout.json.  The physical keyboard uses the Planck MIT (47-key)
 * layout macro, which skips matrix position [3,6] (the unused switch
 * under the 2u spacebar).  In the VIA file that position is filled with
 * KC_NO; here it is simply omitted to match the 47-key macro.
 */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* Layer 0: Base ------------------------------------------------------------------ */
    [0] = LAYOUT_planck_mit(
        /* Row 0 */ KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     KC_BSPC,
        /* Row 1 */ KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_QUOT,
        /* Row 2 */ KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_BSLS,
        /* Row 3 */
            KC_GRV, KC_LCTL, KC_LALT, KC_LGUI, TO(2), LT(1, KC_SPC),
            /* --- matrix [3,6] is skipped by the MIT layout macro --- */
            KC_MINS, KC_EQL, KC_LBRC, KC_RBRC, KC_ENT
    ),

    /* Layer 1: Numpad / Media --------------------------------------------------------- */
    [1] = LAYOUT_planck_mit(
        /* Row 0 */ KC_NO,   KC_P1,   KC_P2,   KC_P3,   KC_P4,   KC_P5,   KC_P6,   KC_P7,   KC_P8,   KC_P9,   KC_P0,    KC_NO,
        /* Row 1 */ KC_NO,   S(KC_1), S(KC_2), S(KC_3), S(KC_4), S(KC_5), S(KC_6), S(KC_7), S(KC_8), S(KC_9), S(KC_0), KC_NO,
        /* Row 2 */ KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,
        /* Row 3 */
            KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
            /* skip [3,6] */
            KC_VOLD, KC_VOLU, RGB_VAD, RGB_VAI, KC_NO
    ),

    /* Layer 2: Navigation ------------------------------------------------------------- */
    [2] = LAYOUT_planck_mit(
        /* Row 0 */ TO(0),   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,
        /* Row 1 */ KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_NO,    KC_NO,
        /* Row 2 */ KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,
        /* Row 3 */
            KC_NO, KC_LCTL, KC_NO, KC_NO, KC_NO, KC_NO,
            /* skip [3,6] */
            KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
    ),

    /* Layer 3: Spare (mostly empty) --------------------------------------------------- */
    [3] = LAYOUT_planck_mit(
        /* Row 0 */ KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,
        /* Row 1 */ KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_NO,    KC_NO,
        /* Row 2 */ KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,
        /* Row 3 */
            KC_NO, KC_LCTL, KC_NO, KC_NO, KC_NO, KC_NO,
            /* skip [3,6] */
            KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
    )

};
// clang-format on

#ifdef RGB_MATRIX_ENABLE

/* -------------------------------------------------------------
 * Per-layer RGB matrix handling
 *
 *  Layer 0 : keep the board's default rainbow effect
 *  Layer 1 : solid yellow
 *  Layer 2 : solid green
 *  Layer 3 : solid red
 * -----------------------------------------------------------*/

static void set_layer_color(uint8_t r, uint8_t g, uint8_t b) {
    /* Use the SOLID_COLOR effect so all LEDs show the same colour. */
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
    rgb_matrix_set_color_all(r, g, b);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    uint8_t layer = get_highest_layer(state);

    switch (layer) {
        case 1:
            /* solid yellow */
            set_layer_color(255, 255, 0);
            break;

        case 2:
            /* solid green */
            set_layer_color(0, 255, 0);
            break;

        case 3:
            /* solid red */
            set_layer_color(255, 0, 0);
            break;

        default:
            /* Return to the board's default rainbow effect. */
            rgb_matrix_mode_noeeprom(RGB_MATRIX_CYCLE_ALL);
            break;
    }

    return state;
}

#endif /* RGB_MATRIX_ENABLE */
