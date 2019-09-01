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

extern keymap_config_t keymap_config;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_QWERTY] = LAYOUT_planck_grid_wrapper(M_ORTHO_R2(M_QWERTY_R2), M_ORTHO_R3(M_QWERTY_R3), M_ORTHO_R4(M_QWERTY_R4), M_GRID_R5),
[_COLEMAK] = LAYOUT_planck_grid_wrapper(M_ORTHO_R2(M_COLEMAK_R2), M_ORTHO_R3(M_COLEMAK_R3), M_ORTHO_R4(M_COLEMAK_R4), M_GRID_R5),
[_DVORAK] = LAYOUT_planck_grid_wrapper(M_ORTHO_R2(M_DVORAK_R2), M_ORTHO_R3(M_DVORAK_R3), M_ORTHO_R4(M_DVORAK_R4), M_GRID_R5),
[_MAC] = LAYOUT_planck_grid_wrapper(M_TRANSPA, M_TRANSPA, M_TRANSPA, M_MAC_R5),
// Placeholder:
[_GAME] = LAYOUT_planck_grid_wrapper(M_TRANSPA, M_TRANSPA, M_TRANSPA, M_GAME_R5),
// We populate the game layer just in case
[_GAME_LOWER] = LAYOUT_planck_grid_wrapper(M_LOWER_R2, M_LOWER_R3, M_LOWER_R4, M_GAME_R5),
[_LOWER] = LAYOUT_planck_grid_wrapper(M_LOWER_R2, M_LOWER_R3, M_LOWER_R4, M_LOWER_R5),
[_RAISE] = LAYOUT_planck_grid_wrapper(M_RAISE_R2, M_RAISE_R3, M_RAISE_R4, M_RAISE_R5),
[_ADJUST] = LAYOUT_planck_grid_wrapper(
  M_ADJUST_R2,
  _______, _______, MU_MOD,  AU_ON,   AU_OFF,  MAC_OFF, MAC_ON,  QWERTY,  COLEMAK,  DVORAK,  _______, _______,
  _______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  _______, _______,  _______, _______, _______,
  M_ADJUST_R5
)
};

#ifdef AUDIO_ENABLE
  float plover_song[][2]     = SONG(PLOVER_SOUND);
  float plover_gb_song[][2]  = SONG(PLOVER_GOODBYE_SOUND);
#endif


bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

void encoder_update(bool clockwise) {
  if (muse_mode) {
    if (IS_LAYER_ON(_RAISE)) {
      if (clockwise) {
        muse_offset++;
      } else {
        muse_offset--;
      }
    } else {
      if (clockwise) {
        muse_tempo+=1;
      } else {
        muse_tempo-=1;
      }
    }
  } else {
    if (clockwise) {
      #ifdef MOUSEKEY_ENABLE
        register_code(KC_MS_WH_DOWN);
        unregister_code(KC_MS_WH_DOWN);
      #else
        register_code(KC_PGDN);
        unregister_code(KC_PGDN);
      #endif
    } else {
      #ifdef MOUSEKEY_ENABLE
        register_code(KC_MS_WH_UP);
        unregister_code(KC_MS_WH_UP);
      #else
        register_code(KC_PGUP);
        unregister_code(KC_PGUP);
      #endif
    }
  }
}

void matrix_scan_keymap(void) {
  #ifdef AUDIO_ENABLE
    if (muse_mode) {
      if (muse_counter == 0) {
        uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
        if (muse_note != last_muse_note) {
          stop_note(compute_freq_for_midi_note(last_muse_note));
          play_note(compute_freq_for_midi_note(muse_note), 0xF);
          last_muse_note = muse_note;
        }
      }
      muse_counter = (muse_counter + 1) % muse_tempo;
    }
  #endif
}

bool music_mask_user(uint16_t keycode) {
  switch (keycode) {
    case RAISE:
    case LOWER:
      return false;
    default:
      return true;
  }
}
