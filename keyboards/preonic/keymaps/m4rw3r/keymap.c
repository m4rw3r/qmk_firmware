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

enum preonic_layers {
  _QWERTY,
  _GAME,
  _KEYPAD,
  _LOWER_GAME,
  _LOWER,
  _RAISE,
  _ADJUST
};

enum preonic_keycodes {
  QWERTY = SAFE_RANGE,
  GAME,
  KEYPAD,
  LOWER,
  RAISE,
  BACKLIT,
  KX_AA,
  KX_AE,
  KX_OE,
  KX_EURO,
};

#ifdef AUDIO_ENABLE
float game_on_song[][2]  = SONG(ONE_UP_SOUND);
float game_off_song[][2] = SONG(TERMINAL_SOUND);
#endif

// Bootmagic config so we can check the WIN/ALT swap and determine how to send latin1 keys
extern keymap_config_t keymap_config;

/**
 * Modifications vs the default Preonic layout:
 * 
 * - Moved Ctrl GUI Alt cluster one key to the left
 * - Swapped GUI and Alt to mimic standard Windows keyboard
 */

// TODO: Numeric keypad
// TODO: HJKL with modifier?
// TODO: What to put on the brightness key?
// TODO: Use a mouse-key instead of caps?
// TODO: Support for Swedish layout (something remapping modifiers producing the same output as US)
// TODO: Make sure it matches planck too

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | GUI  |Brite | Alt  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_preonic_grid( \
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, \
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC, \
  KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,  \
  KC_LCTL, KC_LGUI, BACKLIT, KC_LALT, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT  \
),
/* Gaming overrides
 *
 * * Caps Lock replaces ESC, used for push-to-talk in voice
 */
[_GAME] = LAYOUT_preonic_grid( \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  KC_CAPS, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  \
),

/* Keypad layer
 */
[_KEYPAD] = LAYOUT_preonic_grid( \
  _______, _______, _______, _______, _______, _______, KC_PSLS, KC_PAST, KC_PMNS, _______, _______, _______, \
  _______, _______, _______, _______, _______, KC_KP_7, KC_KP_8, KC_KP_9, KC_PPLS, _______, _______, _______, \
  _______, _______, _______, _______, _______, KC_KP_4, KC_KP_5, KC_KP_6, KC_PENT, _______, _______, _______, \
  _______, _______, _______, _______, _______, KC_KP_1, KC_KP_2, KC_KP_3, KC_PDOT, _______, _______, _______, \
  _______, _______, _______, _______, _______, KC_KP_0, KC_KP_0, _______, _______, _______, _______, _______  \
),

/* Gaming lower layer, main modifier layer, one-handed for gaming-actions.
 * 
 * * ESC on Grave, since Caps Lock replaced ESC on base layer
 * * F-keys easily accessible on number-keys
 * * Same mapping as standard LOWER for right side of the keyboard to faciltate typing
 */
[_LOWER_GAME] = LAYOUT_preonic_grid( \
  KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11, \
  _______, _______, _______, _______, _______, _______, _______, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,  KC_F12, \
  _______, _______, _______, _______, _______, _______, _______, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  \
),
/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |   {  |   }  |  |   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO ~ |ISO | |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_preonic_grid( \
  KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR,   KC_LPRN, KC_RPRN, _______, \
  KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR,   KC_LPRN, KC_RPRN, _______, \
  KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS, KC_PLUS,   KC_LCBR, KC_RCBR, KC_PIPE, \
  _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,S(KC_NUHS),S(KC_NUBS),KC_HOME, KC_END,  _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT,   KC_VOLD, KC_VOLU, KC_MPLY \
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |   Å  |   Ä  |   Ö  |      |      |      |   -  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |   €  |      |      |      |ISO # |ISO / |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_preonic_grid( \
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, \
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,  \
  KC_DEL,  KX_AA,   KX_AE,   KX_OE,   _______, _______, _______, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, \
  _______, _______, _______, KX_EURO, _______, _______, _______, KC_NUHS, KC_NUBS, KC_PGUP, KC_PGDN, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY  \
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Reset|      |      |      |      |      |      |      |      |      |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Aud on|AudOff|AGnorm|AGswap|Qwerty|Colemk|Dvorak|      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|MusOff|MidiOn|MidOff|      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_preonic_grid( \
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  \
  _______, RESET,   DEBUG,   _______, _______, _______, _______, TERM_ON, TERM_OFF,_______, _______, KC_DEL,  \
  _______, _______, MU_MOD,  AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, QWERTY,     GAME, _______,  _______, _______, \
  _______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  \
)

};

/* Alt codes for windows */
char *alt_seq_win[][2] = {
  {
    SS_LALT(SS_TAP(X_KP_0)SS_TAP(X_KP_2)SS_TAP(X_KP_2)SS_TAP(X_KP_9)), // Alt+0229 → å
    SS_LALT(SS_TAP(X_KP_0)SS_TAP(X_KP_1)SS_TAP(X_KP_9)SS_TAP(X_KP_7)), // Alt+0197 → Å
  },
  {
    SS_LALT(SS_TAP(X_KP_0)SS_TAP(X_KP_2)SS_TAP(X_KP_2)SS_TAP(X_KP_8)), // Alt+0228 → ä
    SS_LALT(SS_TAP(X_KP_0)SS_TAP(X_KP_1)SS_TAP(X_KP_9)SS_TAP(X_KP_6)), // Alt+0196 → Ä
  },
  {
    SS_LALT(SS_TAP(X_KP_0)SS_TAP(X_KP_2)SS_TAP(X_KP_4)SS_TAP(X_KP_6)), // Alt+0246 → ö
    SS_LALT(SS_TAP(X_KP_0)SS_TAP(X_KP_2)SS_TAP(X_KP_1)SS_TAP(X_KP_4)), // Alt+0214 → Ö
  },
  {
    SS_LALT(SS_TAP(X_KP_0)SS_TAP(X_KP_1)SS_TAP(X_KP_2)SS_TAP(X_KP_8)), // Alt+0128 → €
    SS_LALT(SS_TAP(X_KP_0)SS_TAP(X_KP_1)SS_TAP(X_KP_2)SS_TAP(X_KP_8)), // Alt+0128 → €
  },
};

char *alt_seq_mac[][2] = {
  {
    SS_LALT(SS_TAP(X_A)), // Alt+a → å
    SS_LSFT(SS_LALT(SS_TAP(X_A))), // Alt+A → Å
  },
  {
    SS_LALT(SS_TAP(X_U))SS_TAP(X_A), // Alt+u + a → ä
    SS_LSFT(SS_LALT(SS_TAP(X_U))SS_TAP(X_A)), // Alt+u + A → Ä
  },
  {
    SS_LALT(SS_TAP(X_U))SS_TAP(X_O), // Alt+u + o → ö
    SS_LSFT(SS_LALT(SS_TAP(X_U))SS_TAP(X_O)), // Alt+u + O → Ö
  },
  {
    SS_LALT(SS_LSFT(SS_TAP(X_2))), // Alt+Shift+2 → €
    SS_LSFT(SS_TAP(X_2)), // Alt+Shift+2 → €, Shift already pressed
  },
};

void tap_keycode(uint16_t keycode) {
  register_code(keycode);
  unregister_code(keycode);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  int main_layer;
  int alt_layer;

  switch(keycode) {
  case QWERTY:
    if(record->event.pressed) {
      set_single_persistent_default_layer(_QWERTY);
    }

    return false;
  case GAME:
    if(record->event.pressed) {
      layer_invert(_GAME);

      #ifdef AUDIO_ENABLE
      if(IS_LAYER_ON(_GAME)) {
        PLAY_SONG(game_on_song);
      }
      else {
        PLAY_SONG(game_off_song);
      }
      #endif

      // Turn off Caps if we are leaving _GAME
      if( ! IS_LAYER_ON(_GAME) && host_keyboard_leds() & (1 << USB_LED_CAPS_LOCK)) {
        tap_keycode(KC_CAPS);
      }
    }

    return false;
  case LOWER:
  case RAISE:
    main_layer = keycode == RAISE ? _RAISE : _LOWER;
    // There is no _RAISE_GAME
    alt_layer  = keycode == RAISE ? _RAISE : _LOWER_GAME;

    if(IS_LAYER_ON(_GAME)) {
      // Swap to game layer as primary
      int tmp    = main_layer;
      main_layer = alt_layer;
      alt_layer  = tmp;
    }

    if(record->event.pressed) {
      layer_on(main_layer);

      if(main_layer != alt_layer) {
        layer_off(alt_layer);
      }
    }
    else {
      // Turn off both just in case
      layer_off(main_layer);
      layer_off(alt_layer);
    }

    update_tri_layer(
      IS_LAYER_ON(_GAME) ? _LOWER_GAME : _LOWER,
      _RAISE,
      _ADJUST);

    return false;

  // UNICODE-ish
  case KX_AA:
  case KX_AE:
  case KX_OE:
  case KX_EURO:
  {
    if( ! record->event.pressed) {
      return false;
    }

    uint16_t index = keycode - KX_AA;
    uint8_t  shift = get_mods() & MOD_MASK_SHIFT;

    unregister_code(KC_LSFT); // Temporarily disable both shift keys
    unregister_code(KC_RSFT);

    // If we have swapped left alt and gui we are on a mac
    if(keymap_config.swap_lalt_lgui) {
      send_string(alt_seq_mac[index][(bool)shift]);
    }
    else {
      // Choose Alt code based on which key was pressed and whether Shift was held.
      send_string(alt_seq_win[index][(bool)shift]);
    }
    
    // Restore shift keys to previous state
    if(shift & MOD_BIT(KC_LSFT)) { register_code(KC_LSFT); }
    if(shift & MOD_BIT(KC_RSFT)) { register_code(KC_RSFT); }
    
    return false;
  }
  case BACKLIT:
    if(record->event.pressed) {
      register_code(KC_RSFT);
      #ifdef BACKLIGHT_ENABLE
        backlight_step();
      #endif
      #ifdef __AVR__
      PORTE &= ~(1<<6);
      #endif
    }
    else {
      unregister_code(KC_RSFT);
      #ifdef __AVR__
      PORTE |= (1<<6);
      #endif
    }

    return false;
  }

  return true;
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

void matrix_scan_user(void) {
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
