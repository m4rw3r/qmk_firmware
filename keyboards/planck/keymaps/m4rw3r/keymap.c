/* Copyright 2015-2017 Jack Humbert
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
#include "muse.h"
#include "m4rw3r.h"
#include "m4rw3r_layouts.h"

#define LAYOUT_planck_grid_wrapper(...) LAYOUT_planck_grid(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_BASE] = LAYOUT_planck_grid_wrapper(M_BASE_R2, M_BASE_R3, M_BASE_R4, M_BASE_R5),
[_MAC] = LAYOUT_planck_grid_wrapper(M_TRANSPA, M_TRANSPA, M_TRANSPA, M_MAC_R5),
// Placeholder:
[_GAME] = LAYOUT_planck_grid_wrapper(M_TRANSPA, M_TRANSPA, M_TRANSPA, M_GAME_R5),
[_LOWER] = LAYOUT_planck_grid_wrapper(M_LOWER_R2, M_LOWER_R3, M_LOWER_R4, M_LOWER_R5),
// We populate the game layer just in case
[_GAME_LOWER] = LAYOUT_planck_grid_wrapper(M_LOWER_R2, M_LOWER_R3, M_LOWER_R4, M_GAME_R5),
[_RAISE] = LAYOUT_planck_grid_wrapper(M_RAISE_R2, M_RAISE_R3, M_RAISE_R4, M_RAISE_R5),
[_ADJUST] = LAYOUT_planck_grid_wrapper(
  M_ADJUST_R2,
  _______, _______, _______, AU_ON,   AU_OFF,  _______, M_ADJUST_R3_R, \
  _______, _______, _______, _______, _______, _______, M_ADJUST_R4_R, \
  M_ADJUST_R5
)
};

#ifdef AUDIO_ENABLE
  float plover_song[][2]     = SONG(PLOVER_SOUND);
  float plover_gb_song[][2]  = SONG(PLOVER_GOODBYE_SOUND);
#endif


