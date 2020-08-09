#include QMK_KEYBOARD_H

#define SHIFT_DOWN() (get_mods() & (MOD_BIT(KC_LSFT)|MOD_BIT(KC_RSFT)))
#define KC_FKEYS MO(FKEYS)

// Layers
enum {
    BASE=0,
    SYMNUM,  // Symbols and numbers (activated by holding enter)
    FKEYS,   // Function keys (activated by a thumb button)
};

// Unicode map -- adding German diacritics
enum unicode_names {
    SS_LC,
    SS_UC,
    UU_LC,
    UU_UC,
    AU_LC,
    AU_UC,
    OU_LC,
    OU_UC
};

const uint32_t PROGMEM unicode_map[] = {
    [SS_LC] = 0x00DF, // ß
    [SS_UC] = 0x1E9E, // ẞ
    [UU_LC] = 0x00FC, //ü
    [UU_UC] = 0x00DC, //Ü
    [AU_LC] = 0x00E4, //ä
    [AU_UC] = 0x00C4, //Ä
    [OU_LC] = 0x00F6, //ö
    [OU_UC] = 0x00D6 //Ö
};

// counter that increments on all key press events.  This is needed for our LT
// handling
uint16_t press_counter = 0;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

// Keymap 0: Base layer

[BASE] = LAYOUT_ergodox(
  // left hand ---------------------------------------------------------------------------------------------------
  KC_GESC,        KC_1,           KC_2,           KC_3,           KC_4,           KC_5,           KC_NO,
  KC_TAB,         KC_Q,           KC_W,           KC_E,           KC_R,           KC_T,           KC_BSPACE,
  KC_NO,          KC_A,           KC_S,           KC_D,           KC_F,           KC_G,
  KC_LSFT,        KC_Z,           KC_X,           KC_C,           KC_V,           KC_B,           KC_ENT,
  KC_FKEYS,       KC_LALT,        KC_PGUP,        KC_PGDN,        KC_NO,
  // left thumb --------------------------------------------------------------------------------------------------
                                                                                  MT(MOD_LGUI | MOD_LALT, KC_NO),      MT(MOD_LGUI | MOD_LSFT | MOD_LALT, KC_NO),
                                                                                                  KC_LCTL,
                                                                  KC_LGUI,        KC_LSFT,        KC_LALT,
  // right hand --------------------------------------------------------------------------------------------------
  KC_NO,          KC_6,           KC_7,           KC_8,           KC_9,           KC_0,           KC_MINUS,
  KC_BSPACE,      KC_Y,           KC_U,           KC_I,           KC_O,           KC_P,           KC_BSLS,
                  KC_H,           KC_J,           KC_K,           KC_L,           KC_SCLN,        KC_QUOTE,
  KC_END,         KC_N,           KC_M,           KC_COMMA,       KC_DOT,         KC_SLASH,       KC_RSFT,
                  KC_LEFT,        KC_UP,          KC_DOWN,        KC_RIGHT,       KC_NO,
  // right thumb -------------------------------------------------------------------------------------------------
  KC_NO,            KC_NO,
  KC_NO,
  KC_FKEYS,         KC_ENT,        KC_SPACE
),
// SYMNUM -- numpad and function keys
[SYMNUM] = LAYOUT_ergodox(
  // left hand ---------------------------------------------------------------------------------------------------
  _______,        LALT(KC_1),     LALT(KC_2),     LALT(KC_3),     LALT(KC_4),     LALT(KC_5),     _______,
  _______,        _______,        _______,        _______,        KC_AMPR,        _______,        _______,
  _______,        XP(AU_LC,AU_UC),        XP(SS_LC,SS_UC),        KC_LPRN,        KC_0,           KC_MINS,
  _______,        KC_6,           KC_7,           KC_8,           KC_9,           KC_SLSH,        _______,
  _______,        _______,        _______,        _______,        _______,
  // left thumb --------------------------------------------------------------------------------------------------
                                                                                  _______,        _______,
                                                                                                  _______,
                                                                  _______,        _______,        _______,
  // right hand --------------------------------------------------------------------------------------------------
  _______,        LALT(KC_6),     LALT(KC_7),     LALT(KC_8),     LALT(KC_9),     LALT(KC_0),     _______,
  _______,        KC_PERC,        XP(UU_LC,UU_UC),        KC_LT,          XP(OU_LC,OU_UC),        KC_EXLM,        _______,
                  _______,        _______,        KC_RPRN,        KC_RBRC,        KC_RCBR,        _______,
  _______,        KC_ASTR,        KC_2,           KC_3,           KC_4,           KC_5,           _______,
                  _______,        _______,        _______,        _______,        _______,
  // right thumb -------------------------------------------------------------------------------------------------
  _______,        _______,
  _______,
  _______,        _______,        _______
),
// FKEYS -- function keys
[FKEYS] = LAYOUT_ergodox(
  // left hand ---------------------------------------------------------------------------------------------------
  _______,        KC_F1,          KC_F2,          KC_F3,          KC_F4,          KC_F5,          KC_F6,
  _______,        _______,        _______,        KC_UP,        _______,        _______,        _______,
  _______,        _______,        KC_LEFT,        KC_DOWN,        KC_RIGHT,        _______,
  _______,        _______,        _______,        _______,        _______,        _______,        _______,
  _______,        _______,        _______,        _______,        _______,
  // left thumb --------------------------------------------------------------------------------------------------
                                                                                  _______,        _______,
                                                                                                  _______,
                                                                  _______,        _______,        _______,
  // right hand --------------------------------------------------------------------------------------------------
  KC_F7,          KC_F8,          KC_F9,          KC_F10,         KC_F11,         KC_F12,         _______,
  _______,        _______,        _______,        _______,        _______,        _______,        _______,
                  _______,        _______,        _______,        _______,        _______,        _______,
  _______,        _______,        _______,        _______,        _______,        _______,        _______,
                  _______,        _______,        _______,        _______,        _______,
  // right thumb -------------------------------------------------------------------------------------------------
  _______,        _______,
  _______,
  _______,        _______,        _______
),
};

// Code to handle layer tap.
//
// The default code doesn't work for me, so I rolled my own code.  The main
// difference is that it always tries to send modifier+key combination, rather
// than two keys.  One place where this is noticable is if you tap the key,
// then try hold it.

struct tap_start_info {
    uint16_t timer;
    uint16_t initial_press_counter;
};

static struct tap_start_info tap_start_infos[5];

// Quick check to see if a key is down.  Note that this requires NKRO enabled
static bool key_down(uint8_t code) {
    return (keyboard_report->nkro.bits[code>>3] & 1<<(code&7)) != 0;
}

static bool handle_lt(uint16_t keycode, keyrecord_t *record, uint8_t layer, uint8_t index) {
    struct tap_start_info* tap_start = tap_start_infos + index;

    if(record->event.pressed) {
        layer_on(layer);
        tap_start->timer = timer_read();
        tap_start->initial_press_counter = press_counter;
    } else {
        layer_off(layer);
        // Only click the key if:
        //   - No other keys are pressed between the press and release events
        //   - The release happens before the ONESHOT_TIMEOUT
        if(press_counter == tap_start->initial_press_counter && timer_elapsed(tap_start->timer) < ONESHOT_TIMEOUT) {
            register_code16(keycode);
            unregister_code16(keycode);
        }
    }
    return false;
}

static bool handle_mt(uint16_t keycode, keyrecord_t *record, uint8_t mods, uint8_t index) {
    struct tap_start_info* tap_start = tap_start_infos + index;

    if(record->event.pressed) {
        register_mods(mods);
        tap_start->timer = timer_read();
        tap_start->initial_press_counter = press_counter;
    } else {
        unregister_mods(mods);
        // Only click the key if:
        //   - No other keys are pressed between the press and release events
        //   - The release happens before the ONESHOT_TIMEOUT
        if(press_counter == tap_start->initial_press_counter && timer_elapsed(tap_start->timer) < ONESHOT_TIMEOUT) {
            register_code16(keycode);
            unregister_code16(keycode);
        }
    }
    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if(record->event.pressed) {
        press_counter++;
        // The symbol layer allows sequences repeat the same "physical" key.
        // For example "0)", which is like pressing the "0" key twice in a
        // row.  It's very easy to make a sequence of these where the ")"
        // press comes before the "0" release.  If that happens, force a
        // release of the "0" key, otherwise nothing will happen.
        uint8_t shortcode = keycode & 0xFF;
        if(key_down(shortcode)) {
            unregister_code(shortcode);
        }
    }

    switch(keycode) {
        case KC_ENTER:
            return handle_lt(keycode, record, SYMNUM, 0);

        case KC_TAB:
            return handle_mt(keycode, record, MOD_BIT(KC_LCTL), 1);

        case KC_LSFT:
        case KC_RSFT:
            return handle_mt(KC_ESC, record, MOD_BIT(keycode), 2);
    }
    return true;
}
