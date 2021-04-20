#include QMK_KEYBOARD_H
#include "m4rw3r.h"
#include "m4rw3r_layouts.h"

#define LAYOUT_2u_wrapper(...) LAYOUT_2u(__VA_ARGS__)

#define M_BABYV_BASE_R5     KC_LCTL, LOWER,   KC_LGUI, KC_SPC,  RAISE,   KC_LALT
#define M_BABYV_MAC_R5      _______, _______, _______, _______, _______, _______
#define M_BABYV_GAME_R5     _______, G_LOWER, _______, _______, _______, _______
#define M_BABYV_LOWER_R5    _______, _______, _______, _______, _______, _______
#define M_BABYV_RAISE_R5    _______, _______, _______, _______, _______, _______
#define M_BABYV_ADJUST_R5   _______, _______, _______, _______, _______, _______

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  //[_BASE] = LAYOUT_2u_wrapper(M_BASE_R2, M_BASE_R3, M_BASE_R4, M_BABYV_BASE_R5),
  [_BASE] = LAYOUT_2u_wrapper(M_BASE_R2, M_BASE_R3, M_BASE_R4, M_BABYV_BASE_R5),
  [_MAC] = LAYOUT_2u_wrapper(M_TRANSPA, M_TRANSPA, M_TRANSPA, M_BABYV_MAC_R5),
  // Placeholder:
  [_GAME] = LAYOUT_2u_wrapper(M_TRANSPA, M_TRANSPA, M_TRANSPA, M_BABYV_GAME_R5),
  [_LOWER] = LAYOUT_2u_wrapper(M_LOWER_R2, M_LOWER_R3, M_LOWER_R4, M_BABYV_LOWER_R5),
  // We populate the game layer just in case
  [_GAME_LOWER] = LAYOUT_2u_wrapper(M_LOWER_R2, M_LOWER_R3, M_LOWER_R4, M_BABYV_GAME_R5),
  [_RAISE] = LAYOUT_2u_wrapper(M_RAISE_R2, M_RAISE_R3, M_RAISE_R4, M_BABYV_RAISE_R5),
  [_ADJUST] = LAYOUT_2u_wrapper(
    M_ADJUST_R2,
    RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, _______,    M_ADJUST_R3_R, \
    RGBLAYER,RGB_RMOD,RGB_HUD, RGB_SAD, RGB_VAD, _______,    M_ADJUST_R4_R, \
    M_BABYV_ADJUST_R5
  )
};


