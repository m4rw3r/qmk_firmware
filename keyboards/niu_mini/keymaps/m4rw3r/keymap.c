#include QMK_KEYBOARD_H
#include "m4rw3r.h"
#include "m4rw3r_layouts.h"

#define LAYOUT_planck_grid_wrapper(...) LAYOUT_ortho_4x12(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_QWERTY]     = LAYOUT_planck_grid_wrapper(M_QWERTY,  M_GRID_R5),
[_COLEMAK]    = LAYOUT_planck_grid_wrapper(M_COLEMAK, M_GRID_R5),
[_DVORAK]     = LAYOUT_planck_grid_wrapper(M_DVORAK,  M_GRID_R5),
[_MAC]        = LAYOUT_planck_grid_wrapper(M_TRANSPA, M_TRANSPA, M_TRANSPA, M_MAC_R5),
// TODO: Needs better placeholder
[_GAME]       = LAYOUT_planck_grid_wrapper(M_QWERTY,  M_GAME_R5),
// TODO: Populate
[_KEYPAD]     = LAYOUT_planck_grid_wrapper(M_QWERTY,  M_GRID_R5),
// We populate the game layer just in case
[_GAME_LOWER] = LAYOUT_planck_grid_wrapper(M_LOWER_R2, M_LOWER_R3, M_LOWER_R4, M_GAME_R5),
[_LOWER]      = LAYOUT_planck_grid_wrapper(M_LOWER_R2, M_LOWER_R3, M_LOWER_R4, M_LOWER_R5),
[_RAISE]      = LAYOUT_planck_grid_wrapper(M_RAISE_R2, M_RAISE_R3, M_RAISE_R4, M_RAISE_R5),
// Adjust layer is similar to planck/preonic, but with RGB controls instead of audio, and game layer toggle is removed
[_ADJUST]     = LAYOUT_planck_grid_wrapper( \
  _______, RESET,   DEBUG,   _______, _______, _______, _______, TERM_ON, TERM_OFF,_______, _______, KC_DEL,  \
  _______, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, MAC_OFF, MAC_ON,  QWERTY,  COLEMAK, DVORAK,  _______, _______, \
  _______, BL_TOGG, BL_STEP, _______, _______, _______, _______, _______, KEYPAD,  _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  \
),
};