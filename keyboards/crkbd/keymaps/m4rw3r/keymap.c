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
#define THUMB_CLUSTER KC_LALT,  LOWER,  KC_LCTL,      KC_SPACE,  RAISE, KC_LGUI

// TODO: PgUp, PgDown, Home, End
// TODO: Media controls
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
  RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, _______,    KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,  _______, _______, \
  RGBLAYER,RGB_RMOD,RGB_HUD, RGB_SAD, RGB_VAD, _______,    KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, _______, KC_MPLY, \
                        _______, _______, _______, _______, _______, _______ \
    ),
};

void matrix_init_keymap(void) {
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

// When add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

void matrix_scan_keymap(void) {
   iota_gfx_task();
}

void matrix_render_user(struct CharacterMatrix *matrix) {
  if (is_master) {
    // If you want to change the display of OLED, you need to change here
    matrix_write(matrix, "Layer: ");
    matrix_write_ln(matrix, get_layer_state_name());
    // matrix_write_ln(matrix, read_keylog());
    //matrix_write_ln(matrix, read_keylogs());
    //matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
    //matrix_write_ln(matrix, read_host_led_state());
    //matrix_write_ln(matrix, read_timelog());
  } else {
    matrix_write(matrix, read_logo());
  }
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;
  matrix_clear(&matrix);
  matrix_render_user(&matrix);
  matrix_update(&display, &matrix);
}
#endif//SSD1306OLED