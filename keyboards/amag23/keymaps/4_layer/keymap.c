/* Copyright 2021
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

// Defines names for use in layer keycodes and the keymap
enum layer_names { BASE, FN1, FN2, FN3 };

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT_all(
        TO(0), KC_F14, KC_F15, KC_F16, KC_F17, KC_F18,
        TO(1), LCTL(KC_F14), LCTL(KC_F15), LCTL(KC_F16), LCTL(KC_F17), LCTL(KC_F18),
        TO(2), LALT(KC_F14), LALT(KC_F15), LALT(KC_F16), LALT(KC_F17), LALT(KC_F18),
        TO(3), LGUI(KC_F14), LGUI(KC_F15), LGUI(KC_F16), OSM(MOD_LSFT)
        ),
    [FN1]  = LAYOUT_all(
        KC_TRNS, C(A(KC_F14)), C(A(KC_F15)), C(A(KC_F16)), C(A(KC_F17)), C(A(KC_F18)),
        KC_TRNS, C(G(KC_F14)), C(G(KC_F15)), C(G(KC_F16)), C(G(KC_F17)), C(G(KC_F18)),
        KC_TRNS, A(G(KC_F14)), A(G(KC_F15)), A(G(KC_F16)), A(G(KC_F17)), A(G(KC_F18)),
        KC_TRNS, C(A(G(KC_F14))), C(A(G(KC_F15))), C(A(G(KC_F16))), OSM(MOD_LSFT)
        ),
    [FN2]  = LAYOUT_all(
        KC_TRNS, KC_MPRV, KC_MPLY, KC_MNXT, KC_NO, KC_NO,
        KC_TRNS, KC_NO, KC_VOLU, KC_NO, KC_NO, KC_NO,
        KC_TRNS, KC_F19, KC_MUTE, KC_NO, KC_NO, KC_NO,
        KC_TRNS, KC_NO, KC_VOLD, KC_NO, KC_NO
        ),
    [FN3]  = LAYOUT_all(
        KC_TRNS, KC_PSLS, KC_PAST, KC_P7, KC_P8, KC_P9,
        KC_TRNS, KC_PMNS, KC_PPLS, KC_P4, KC_P5, KC_P6,
        KC_TRNS, KC_NO, KC_TAB, KC_P1, KC_P2, KC_P3,
        KC_TRNS, KC_PDOT, KC_PCMM, KC_P0, KC_PENT
        )
};

// Light LEDs 6 to 9 and 12 to 15 red when caps lock is active. Hard to ignore!
const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 7, HSV_RED}       // Light 1 LEDs, starting with LED 0
);

const rgblight_segment_t PROGMEM my_base_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 7, HSV_RED}       // Light 1 LEDs, starting with LED 0
);
// Light LEDs 9 & 10 in cyan when keyboard layer 1 is active
const rgblight_segment_t PROGMEM my_fn1_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 7, HSV_CYAN}
);
// Light LEDs 11 & 12 in purple when keyboard layer 2 is active
const rgblight_segment_t PROGMEM my_fn2_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 7, HSV_PURPLE}
);
// Light LEDs 13 & 14 in green when keyboard layer 3 is active
const rgblight_segment_t PROGMEM my_fn3_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 7, HSV_GREEN}
);

// Now define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_capslock_layer,
    my_base_layer,
    my_fn1_layer,    // Overrides caps lock layer
    my_fn2_layer,    // Overrides other layers
    my_fn3_layer     // Overrides other layers
);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
}

bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(0, led_state.caps_lock);
    return true;
}

layer_state_t default_layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(1, layer_state_cmp(state, BASE));
    return state;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(2, layer_state_cmp(state, FN1));
    rgblight_set_layer_state(3, layer_state_cmp(state, FN2));
    rgblight_set_layer_state(4, layer_state_cmp(state, FN3));
    return state;
}

// clang-format on
