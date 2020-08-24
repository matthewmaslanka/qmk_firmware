// Based on default keymap.
// Layers for Sibelius, Dorico, and Finale
// Modifiers on thumb keys where possible.

#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"

#define BASE 0 // default layer
#define SHFT 1 // arrow keys, numpad, media control, display control, reset
#define LAYR 2 // Layer hub
#define SIB1 3 // Sibelius Base Layer
#define SIB2 4 // Sibelius Shift Layer
#define QWERTY 10 // QWERTY Shift layer




enum combos {
  QZ_A
};

const uint16_t PROGMEM qz_combo[] = {KC_Q, KC_Z, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [QZ_A] = COMBO(qz_combo, KC_A)
};



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[BASE] = LAYOUT_ergodox(  // layer 0 : default
        // left hand
        KC_GESC,        KC_1,         KC_2,      KC_3,     KC_4,   KC_5,   MO(LAYR),
        KC_TAB,         KC_Q,         KC_W,      KC_E,     KC_R,   KC_T,   KC_BSPC,
        KC_NO,          KC_A,         KC_S,      KC_D,     KC_F,   KC_G,
        MO(SHFT),        KC_Z,         KC_X,      KC_C,     KC_V,   KC_B,   KC_ENT,
        KC_GRV,         KC_NO,        KC_LBRC,   KC_RBRC,  KC_SPC,
                                              MT(MOD_LALT | MOD_LGUI, KC_NO),  MT(MOD_LALT | MOD_LGUI | MOD_LSFT, KC_NO),
                                                              KC_LCTL,
                                               MT(MOD_LGUI,KC_SPC),MT(MOD_LSFT,KC_ENT),KC_LALT,
        // right hand
             LGUI(KC_S),     KC_6,    KC_7,   KC_8,     KC_9,     KC_0,      KC_MINS,
             KC_BSPC,        KC_Y,    KC_U,   KC_I,     KC_O,     KC_P,      KC_EQL,
                             KC_H,    KC_J,   KC_K,     KC_L,     KC_SCLN,   KC_QUOT,
             KC_ENT,         KC_N,    KC_M,   KC_COMM,  KC_DOT,   KC_SLSH,   MO(SHFT),
                             KC_LEFT, KC_UP,  KC_DOWN,  KC_RIGHT, KC_NO,
             MT(MOD_LALT | MOD_LGUI | MOD_LSFT, KC_NO),        MT(MOD_LALT | MOD_LGUI, KC_NO),
             KC_LCTL,
             KC_LALT,MT(MOD_LSFT,KC_ENT),MT(MOD_LGUI,KC_SPC)
    ),

// SHIFT arrow keys, numpad, media control, display control, reset
[SHFT] = LAYOUT_ergodox(
       // left hand
       _______, KC_MPRV, KC_MPLY, KC_MNXT, KC_VOLD, KC_VOLU, KC_MUTE, 
       _______, _______, _______, KC_UP,   _______, _______, _______, 
       _______, _______, KC_LEFT, KC_DOWN, KC_RIGHT,_______, 
       _______, _______, _______, _______, _______, _______, _______, 
       _______, _______, KC_BRID, KC_BRIU, _______, 
                                                    _______, _______, 
                                                             _______, 
                                           _______, _______, _______, 
       // right hand
       RESET,   _______,  _______,  _______,  _______,  _______,  _______,
       _______, _______,  KC_KP_7,  KC_KP_8,  KC_KP_9,  _______,  _______,
                _______,  KC_KP_4,  KC_KP_5,  KC_KP_6,  _______,  _______,
       _______, _______,  KC_KP_1,  KC_KP_2,  KC_KP_3,  _______,  _______,
                          KC_KP_0,  _______,  KC_KP_0,  _______,  KC_KP_ENTER,
       _______, _______,
       _______,
       _______, _______, _______
),

// Layer Switch
[LAYR] = LAYOUT_ergodox(
    // left hand
       _______, _______, _______, _______, _______, _______, _______,
       _______, _______, _______, _______, _______, _______, _______,
       _______, _______, TO(SIB1),_______, _______, _______,
       _______, _______, _______, _______, _______, _______, _______,
       _______, _______, _______, _______, _______,
                                           _______, _______,
                                                    _______,
                                  _______, _______, _______,
    // right hand
       _______,  _______, _______, _______, _______, _______, _______,
       _______,  _______, _______, _______, _______, _______, _______,
                 _______, _______, _______, _______, _______, _______,
       _______,  _______, _______, _______, _______, _______, _______,
                          _______, _______, _______, _______, _______,
       _______, _______,
       _______,
       _______, _______, _______
),
// Sibelius Base
[SIB1] = LAYOUT_ergodox(
    // left hand
       _______,   _______, _______, KC_D,    KC_P,    LGUI(KC_S), TO(BASE),
       _______,   _______, _______, KC_UP,   _______, _______,    _______,
       _______,   _______, KC_LEFT, KC_DOWN, KC_RIGHT,KC_H,
       MO(QWERTY),_______, _______, _______, _______, KC_BSLASH,  _______,
       _______,   KC_F,    _______, _______, _______,
                                             _______, _______,
                                                      _______,
                                    _______, _______, _______,
    // right hand
       _______, KC_1,     KC_2,     _______,  _______,  KC_4,     KC_ESC,
       _______, KC_R,     KC_KP_7,  KC_KP_8,  KC_KP_9,  KC_T,     _______,
                _______,  KC_KP_4,  KC_KP_5,  KC_KP_6,  _______,  _______,
       _______, _______,  KC_KP_1,  KC_KP_2,  KC_KP_3,  _______,  MO(SIB2),
                          KC_KP_0,  KC_Z,     KC_KP_DOT,KC_F,     KC_KP_ENTER,
       _______, _______,
       _______,
       _______, _______, _______
),
// Sibelius Shift
[SIB2] = LAYOUT_ergodox(
    // left hand
       _______, _______, _______, _______, _______, _______, _______,
       _______, _______, _______, _______, _______, _______, _______,
       _______, _______, _______, _______, _______, _______,
       _______, _______, _______, _______, _______, _______, _______,
       _______, _______, _______, _______, _______,
                                           _______, _______,
                                                    _______,
                                  _______, _______, _______,
    // right hand
       _______,  _______, _______, _______, _______, _______, _______,
       _______,  _______, _______, KC_UP, _______, _______, _______,
                 _______, KC_LEFT, KC_DOWN, KC_RIGHT,_______, _______,
       _______,  _______, _______, _______, _______, _______, _______,
                          _______, _______, _______, _______, _______,
       _______, _______,
       _______,
       _______, _______, _______
),

[QWERTY] = LAYOUT_ergodox(  // layer 0 : default
        // left hand
        KC_GESC,        KC_1,         KC_2,      KC_3,     KC_4,   KC_5,   MO(LAYR),
        KC_TAB,         KC_Q,         KC_W,      KC_E,     KC_R,   KC_T,   KC_BSPC,
        KC_NO,          KC_A,         KC_S,      KC_D,     KC_F,   KC_G,
        MO(SHFT),        KC_Z,         KC_X,      KC_C,     KC_V,   KC_B,   KC_ENT,
        KC_GRV,         KC_NO,        KC_LBRC,   KC_RBRC,  KC_SPC,
                                              MT(MOD_LCTL | MOD_LGUI, KC_NO),  MT(MOD_LCTL | MOD_LGUI | MOD_LSFT, KC_NO),
                                                              KC_LCTL,
                                               MT(MOD_LGUI,KC_SPC),MT(MOD_LSFT,KC_ENT),KC_LALT,
        // right hand
             LGUI(KC_S),     KC_6,    KC_7,   KC_8,     KC_9,     KC_0,      KC_MINS,
             KC_BSPC,        KC_Y,    KC_U,   KC_I,     KC_O,     KC_P,      KC_EQL,
                             KC_H,    KC_J,   KC_K,     KC_L,     KC_SCLN,   KC_QUOT,
             KC_ENT,         KC_N,    KC_M,   KC_COMM,  KC_DOT,   KC_SLSH,   MO(SHFT),
                             KC_LEFT, KC_UP,  KC_DOWN,  KC_RIGHT, KC_NO,
             MT(MOD_LCTL | MOD_LGUI | MOD_LSFT, KC_NO),        MT(MOD_LCTL | MOD_LGUI, KC_NO),
             KC_LCTL,
             KC_LALT,MT(MOD_LSFT,KC_ENT),MT(MOD_LGUI,KC_SPC)
    ),
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {

};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

  uint8_t layer = biton32(layer_state);

  ergodox_board_led_off();
  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();
  switch (layer) {
    // TODO: Make this relevant to the ErgoDox EZ.
    case SHFT:
      ergodox_right_led_1_on();
      break;
    case SIB1:
      ergodox_right_led_2_on();
      break;
    default:
      // none
      break;
  }

};
