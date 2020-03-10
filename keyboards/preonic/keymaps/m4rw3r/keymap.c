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
  KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11, \
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
 * |      | Reset|      |      |      |MacOff|MacOn |      |      |      |      |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Aud on|AudOff|      | Left | Down |  Up  |Right |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|MusOff|MidiOn|MidOff|      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Prev |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_preonic_grid_wrapper( \
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  \
  M_ADJUST_R2, \
  _______, _______, MU_MOD,  AU_ON,   AU_OFF,  _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,  _______, _______, \
  _______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  GAME,    _______, _______, _______, _______, \
  M_ADJUST_R5 \
)
};

bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

void encoder_update_user(uint8_t index, bool clockwise) {
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
      register_code(KC_PGDN);
      unregister_code(KC_PGDN);
    } else {
      register_code(KC_PGUP);
      unregister_code(KC_PGUP);
    }
  }
}

void dip_update(uint8_t index, bool active) {
  switch (index) {
    case 0:
      if (active) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      break;
    case 1:
      if (active) {
        muse_mode = true;
      } else {
        muse_mode = false;
        #ifdef AUDIO_ENABLE
          stop_all_notes();
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
