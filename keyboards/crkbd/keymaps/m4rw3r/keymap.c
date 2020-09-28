#include QMK_KEYBOARD_H
#include "m4rw3r.h"
#include "m4rw3r_layouts.h"

extern keymap_config_t keymap_config;
extern uint8_t is_master;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

#define LAYOUT_wrapper(...) LAYOUT(__VA_ARGS__)

// TODO: Drop CTRL on CRKBD to allow for a VIM-layer?
#define THUMB_CLUSTER KC_LCTL,  LOWER,  KC_LGUI,      KC_SPACE,  RAISE, KC_LALT

// TODO: PgUp, PgDown, Home, End
// TODO: Iron out the thumb-clusters

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_wrapper(\
        M_BASE_R2,\
        M_BASE_R3,\
        M_BASE_R4,\
        THUMB_CLUSTER\
    ),
    [_MAC] = LAYOUT_wrapper(\
        M_TRANSPA,\
        M_TRANSPA,\
        M_TRANSPA,\
        KC_LALT,  LOWER,  KC_LGUI,      KC_SPACE,  RAISE, KC_LCTL\
    ),
    [_GAME] = LAYOUT_wrapper(\
        M_TRANSPA,\
        M_TRANSPA,\
        M_TRANSPA,\
                        _______,  _______,  G_LOWER, _______, _______, _______ \
    ),
    [_GAME_LOWER] = LAYOUT_wrapper(\
        M_TRANSPA,\
        M_TRANSPA,\
        M_TRANSPA,\
                        _______, _______, _______, _______, _______, _______ \
    ),
    [_LOWER] = LAYOUT_wrapper(\
        M_LOWER_R2,\
        M_LOWER_R3,\
        M_LOWER_R4,\
                        _______, _______, _______, _______, _______, _______ \
    ),
    [_RAISE] = LAYOUT_wrapper(\
        M_RAISE_R2,\
        M_RAISE_R3,\
        M_RAISE_R4,\
                        _______, _______, _______, _______, _______, _______ \
    ),
    [_ADJUST] = LAYOUT_wrapper(\
        M_ADJUST_R2,\
  RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, _______,    M_ADJUST_R3_R, \
  RGBLAYER,RGB_RMOD,RGB_HUD, RGB_SAD, RGB_VAD, _______,    M_ADJUST_R4_R, \
                        _______, _______, _______, _______, _______, _______ \
    ),
};

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return rotation;
    }  else {
        return OLED_ROTATION_180;
    }
}

// When add source files to SRC in rules.mk, you can use functions.
const char *read_logo(void);

void oled_task_user(void) {
  if (is_keyboard_master()) {
    oled_write("Layer: ", false);
    oled_write_ln(get_layer_state_name(), false);
  } else {
    oled_write(read_logo(), false);
  }
}

#endif// OLED_DRIVER_ENABLE