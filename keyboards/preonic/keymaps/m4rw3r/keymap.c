#include QMK_KEYBOARD_H
#include "muse.h"
#include "m4rw3r.h"
#include "m4rw3r_layouts.h"

#define LAYOUT_preonic_grid_wrapper(...) LAYOUT_preonic_grid(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_BASE] = LAYOUT_preonic_grid_wrapper(M_BASE_R1, M_BASE_R2, M_BASE_R3, M_BASE_R4, M_BASE_R5),
[_MAC] = LAYOUT_preonic_grid_wrapper(M_TRANSPA, M_TRANSPA, M_TRANSPA, M_TRANSPA, M_MAC_R5),
/* Gaming overrides
 *
 * * Caps Lock replaces ESC, used for push-to-talk in voice
 */
[_GAME] = LAYOUT_preonic_grid( \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, G_LOWER, _______, _______, _______, _______, _______, _______, _______  \
),

/* Gaming lower layer, main modifier layer, one-handed for gaming-actions.
 * 
 * * ESC on Grave, since Caps Lock replaced ESC on base layer
 * * F-keys easily accessible on number-keys
 * * Same mapping as standard LOWER for right side of the keyboard to faciltate typing
 * * Moved Home, Page Down, Page Up, and End to this layer on arrow keys
 */
[_GAME_LOWER] = LAYOUT_preonic_grid_wrapper( \
  M_LOWER_R1_L, M_LOWER_R1_R(KC_F11), \
  _______, _______, _______, _______, _______, _______, M_LOWER_R2_R(KC_F12), \
  _______, _______, _______, _______, _______, _______, M_LOWER_R3_R, \
  _______, _______, _______, _______, _______, _______, M_LOWER_R4_R, \
  _______, _______, _______, _______, _______, _______, M_LOWER_R5_R  \
),

[_LOWER] = LAYOUT_preonic_grid_wrapper(M_LOWER_R1, M_LOWER_R2, M_LOWER_R3, M_LOWER_R4, M_LOWER_R5),
[_RAISE] = LAYOUT_preonic_grid_wrapper(M_RAISE_R1, M_RAISE_R2, M_RAISE_R3, M_RAISE_R4, M_RAISE_R5),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Reset| Debug|EEPRES|OS:Lnx|OS:Win|OS:Mac|      |      |TermOf|TermOn|  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Aud on|AudOff|      | Left | Down |  Up  |Right | Vol+ | Next |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      | GAME |      |      |      | Home | PgDn | PgUp | End  | Vol- | Play |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Prev |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_preonic_grid_wrapper( \
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  \
  M_ADJUST_R2, \
  _______, _______, _______, AU_ON,   AU_OFF,  _______, M_ADJUST_R3_R, \
  _______, _______, GAME,    _______, _______, _______, M_ADJUST_R4_R, \
  M_ADJUST_R5 \
)
};
