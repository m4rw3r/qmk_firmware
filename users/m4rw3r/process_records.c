#include "process_records.h"

// Bootmagic config so we can check the WIN/ALT swap and determine how to send latin1 keys
extern keymap_config_t keymap_config;

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
    SS_LALT(SS_TAP(X_U))SS_LSFT(SS_TAP(X_A)), // Alt+u + A → Ä
  },
  {
    SS_LALT(SS_TAP(X_U))SS_TAP(X_O), // Alt+u + o → ö
    SS_LALT(SS_TAP(X_U))SS_LSFT(SS_TAP(X_O)), // Alt+u + O → Ö
  },
  {
    SS_LALT(SS_LSFT(SS_TAP(X_2))), // Alt+Shift+2 → €
    SS_LALT(SS_LSFT(SS_TAP(X_2))), // Alt+Shift+2 → €
  },
};

void tap_keycode(uint16_t keycode) {
  register_code(keycode);
  unregister_code(keycode);
}

// TODO: void keyboard_post_init_user(void), init leds in this

uint32_t layer_state_set_user(uint32_t state) {
  state = update_tri_layer_state(
    state,
    IS_LAYER_STATE_ON(state, _GAME) ? _GAME_LOWER : _LOWER,
    _RAISE,
    _ADJUST);

  // Turn off Caps if we are leaving _GAME
  if(IS_LAYER_STATE_DEACTIVATING(state, _GAME) && IS_HOST_LED_ON(USB_LED_CAPS_LOCK)) {
    tap_keycode(KC_CAPS);
  }
  // Turn on Num Lock if we are entering the keypad
  if(IS_LAYER_STATE_ACTIVATING(state, _KEYPAD) && ! IS_HOST_LED_ON(USB_LED_NUM_LOCK)) {
    tap_keycode(KC_NLCK);
  }

  #ifdef AUDIO_ENABLE
  layer_state_play_audio(state);
  #endif

  // TODO: RGB
  // TODO: Sound

  return layer_state_set_keymap(state);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch(keycode) {
  case KC_QWERTY ... KC_DVORAK:
    if(record->event.pressed) {
      set_single_persistent_default_layer(keycode - KC_QWERTY);
    }

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
  case KC_BACKLIT:
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

  return process_record_keymap(keycode, record);
};