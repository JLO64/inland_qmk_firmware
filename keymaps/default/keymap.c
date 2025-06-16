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


enum custom_keycodes {
    QMKBEST = SAFE_RANGE,
    MACCY,
    MACOS_SCREENLOCK,
    FULL_SCREEN_WINDOW,
    TILE_LEFT,
    TILE_RIGHT,
    MAXIMIZE_WINDOW,
};
 

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* Layer 0: Base ------------------------------------------------------------------ */
    [0] = LAYOUT_planck_mit(
        /* Row 0 */ KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     KC_BSPC,
        /* Row 1 */ KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_QUOT,
        /* Row 2 */ KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_BSLS,
        /* Row 3 */
            KC_GRV, KC_LCTL, KC_LALT, TO(2), KC_LGUI, LT(1, KC_SPC),
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
            KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
    ),

    /* Layer 2: Vim Navigation --------------------------------------------------------- */
    [2] = LAYOUT_planck_mit(
        /* Row 0 */ TO(0),   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,    MACOS_SCREENLOCK,
        /* Row 1 */ KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_NO,    KC_NO,
        /* Row 2 */ KC_NO,   KC_NO,   KC_NO,   MACCY,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,
        /* Row 3 */
            KC_NO, KC_LCTL, KC_NO, KC_NO, KC_NO, KC_NO,
            /* skip [3,6] */
            KC_VOLD, KC_VOLU, KC_NO, KC_NO, KC_ENT
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

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    uint8_t layer = get_highest_layer(layer_state);
    
    switch (layer) {
        case 0:
            /* Animated random colors - change every 100ms */
            {
                static uint32_t last_update = 0;
                static uint32_t seed = 1;
                uint32_t now = timer_read32();
                
                if (now - last_update > 100) {
                    seed = (seed * 1103515245 + 12345) & 0x7fffffff;
                    last_update = now;
                }
                
                for (uint8_t i = led_min; i < led_max; i++) {
                    uint32_t key_seed = seed + i * 2654435761UL;
                    // uint8_t r = (key_seed >> 16) & 0xFF;
                    // uint8_t g = (key_seed >> 8) & 0xFF;
                    // uint8_t b = key_seed & 0xFF;
                    uint8_t r_var = (key_seed & 0xFF) % 120;
                    uint8_t g_var = ((key_seed >> 8) & 0xFF) % 80;
                    uint8_t b_var = ((key_seed >> 16) & 0xFF) % 160;
                    uint8_t r = 161 - r_var;
                    uint8_t g = g_var;
                    uint8_t b = 246 - b_var;
                    rgb_matrix_set_color(i, r, g, b);
                }
            }
            return true;

        case 1:
            /* Turn off all LEDs first */
            for (uint8_t i = led_min; i < led_max; i++) {
                rgb_matrix_set_color(i, 0, 0, 0);
            }
            /* yellow only on Q-P (row 0, LEDs 1-10) and A-; (row 1, LEDs 13-22) */
            for (uint8_t i = 1; i <= 10; i++) {  /* Q-P keys */
                rgb_matrix_set_color(i, 255, 255, 0);
            }
            for (uint8_t i = 13; i <= 22; i++) { /* A-; keys */
                rgb_matrix_set_color(i, 255, 255, 0);
            }
            return true;

        case 2:
            /* Turn off all LEDs first */
            for (uint8_t i = led_min; i < led_max; i++) {
                rgb_matrix_set_color(i, 0, 0, 0);
            }
            /* green only on active navigation keys */
            rgb_matrix_set_color(0, 0, 255, 0);   /* KC_ESC */
            rgb_matrix_set_color(11, 0, 255, 0);   /* KC_BSPC */
            for (uint8_t i = 18; i <= 21; i++) {
                rgb_matrix_set_color(i, 0, 255, 0);
            }
            rgb_matrix_set_color(27, 0, 255, 0);   /* KC_C */
            rgb_matrix_set_color(37, 0, 255, 0);  /* KC_LCTL */
            rgb_matrix_set_color(42, 0, 255, 0);  /* KC_LCTL */
            rgb_matrix_set_color(43, 0, 255, 0);  /* KC_LCTL */
            return true;

        case 3:
            /* solid red */
            for (uint8_t i = led_min; i < led_max; i++) {
                rgb_matrix_set_color(i, 255, 0, 0);
            }
            return true;

        default:
            return false;
    }
}

layer_state_t layer_state_set_user(layer_state_t state) {
    /* For all layers, use solid color mode so indicators can override */
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);

    return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case MACOS_SCREENLOCK:
        if (record->event.pressed) {
            // SEND_STRING(SS_DOWN(KC_LCTL) SS_DOWN(KC_LCMD) "Q");
            register_code(KC_LCTL);
            register_code(KC_LCMD);
            register_code(KC_Q);
            unregister_code(KC_LCTL);
            unregister_code(KC_LCMD);
            unregister_code(KC_Q);
        }
        break;
    case MACCY:
        if (record->event.pressed) {
            register_code(KC_LSFT);
            register_code(KC_LCMD);
            register_code(KC_LBRC);
            unregister_code(KC_LSFT);
            unregister_code(KC_LCMD);
            unregister_code(KC_LBRC);
        }
        break;
    case TILE_LEFT:
        if (record->event.pressed) {
            register_code(KC_LCTL);
            register_code(KC_LOPT);
            register_code(KC_LEFT);
            unregister_code(KC_LCTL);
            unregister_code(KC_LOPT);
            unregister_code(KC_LEFT);
        }
        break;
    case TILE_RIGHT:
      if (record->event.pressed) {
            register_code(KC_LCTL);
            register_code(KC_LOPT);
            register_code(KC_RGHT);
            unregister_code(KC_LCTL);
            unregister_code(KC_LOPT);
            unregister_code(KC_RGHT);
        }
        break;
    case MAXIMIZE_WINDOW:
        if(record->event.pressed) {
            register_code(KC_LCTL);
            register_code(KC_LOPT);
            register_code(KC_UP);
            unregister_code(KC_LCTL);
            unregister_code(KC_LOPT);
            unregister_code(KC_UP);
        }
        break;
  }
    return true;
};
 

#endif /* RGB_MATRIX_ENABLE */
