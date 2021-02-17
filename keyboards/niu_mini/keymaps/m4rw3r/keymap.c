#include QMK_KEYBOARD_H
#include "m4rw3r.h"
#include "m4rw3r_layouts.h"

#define LAYOUT_planck_grid_wrapper(...) LAYOUT_ortho_4x12(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_BASE] = LAYOUT_planck_grid_wrapper(M_BASE_R2, M_BASE_R3, M_BASE_R4, M_BASE_R5),
[_MAC] = LAYOUT_planck_grid_wrapper(M_TRANSPA, M_TRANSPA, M_TRANSPA, M_MAC_R5),
// Placeholder:
[_GAME] = LAYOUT_planck_grid_wrapper(M_TRANSPA, M_TRANSPA, M_TRANSPA, M_GAME_R5),
[_LOWER] = LAYOUT_planck_grid_wrapper(M_LOWER_R2, M_LOWER_R3, M_LOWER_R4, M_LOWER_R5),
// We populate the game layer just in case
[_GAME_LOWER] = LAYOUT_planck_grid_wrapper(M_LOWER_R2, M_LOWER_R3, M_LOWER_R4, M_GAME_R5),
[_RAISE] = LAYOUT_planck_grid_wrapper(M_RAISE_R2, M_RAISE_R3, M_RAISE_R4, M_RAISE_R5),
// Adjust layer is similar to planck/preonic, but with RGB controls instead of audio, and game layer toggle is removed
[_ADJUST] = LAYOUT_planck_grid_wrapper( \
  M_ADJUST_R2, \
  RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, _______, M_ADJUST_R3_R, \
  RGBLAYER,RGB_RMOD,RGB_HUD, RGB_SAD, RGB_VAD, _______, M_ADJUST_R4_R, \
  BL_TOGG, BL_STEP, _______, _______, _______, _______, _______, _______, KC_MPRV, KC_BRID, KC_BRIU, _______  \
),
};