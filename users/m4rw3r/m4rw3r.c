#include "m4rw3r.h"
#include "eeprom.h"

#if defined(__AVR__)
  #include <stdio.h>
#else
  // ChibiOS does not have snprintf use a similar interface

  #include "chprintf.h"
  #define snprintf chsnprintf
#endif

user_config_t user_config;

// Default implementation
__attribute__((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  return true;
}

// Default implementation
__attribute__((weak))
layer_state_t layer_state_set_keymap(layer_state_t state) {
  return state;
}

// Default implementation
__attribute__((weak))
void keyboard_pre_init_keymap(void) { }

// Default implementation
__attribute__((weak))
void keyboard_post_init_keymap(void) { }

// Default implementation
__attribute__((weak))
void eeconfig_init_keymap(void) { }

// Default implementation
__attribute__((weak))
void matrix_init_keymap(void) { }

// Default implementation
__attribute__((weak))
void matrix_scan_keymap(void) { }

void keyboard_pre_init_user(void) {
  keyboard_pre_init_keymap();
}

void matrix_init_user(void) {
  matrix_init_keymap();
}

// Loads data from EEPROM and inits user stuff
void keyboard_post_init_user(void) {
  user_config.raw = eeconfig_read_user();

  if(user_config.is_mac) {
    layer_on(_MAC);
  }

  #ifdef RGBLIGHT_ENABLE
  layer_state_set_rgb(layer_state);
  #endif

  keyboard_post_init_keymap();
}

void user_config_save(void) {
  eeconfig_update_user(user_config.raw);
}

// Contains default configuration for when EEPROM is reset
void eeconfig_init_user(void) {
  user_config.raw = 0;
  user_config.use_rgb_layer_indicators = true;

  user_config_save();

  #ifdef RGBLIGHT_ENABLE
  eeconfig_init_rgb();
  #endif

  eeconfig_init_keymap();
}

void matrix_scan_user(void) {
  matrix_scan_keymap();
}

void set_mac_layer(bool enabled) {
  // Only update if different, saves EEPROM
  if(user_config.is_mac != enabled) {
    user_config.is_mac = enabled;

    user_config_save();

    if(user_config.is_mac) {
      layer_on(_MAC);
    }
    else {
      layer_off(_MAC);
    }
  }
}

void set_rgb_layer_indicators(bool enabled) {
  // Only update if different, saves EEPROM
  if(user_config.use_rgb_layer_indicators != enabled) {
    user_config.use_rgb_layer_indicators = enabled;

    user_config_save();

    #ifdef RGBLIGHT_ENABLE
    if(user_config.use_rgb_layer_indicators) {
      rgblight_enable();
      layer_state_set_rgb(layer_state);
    }
    #endif
  }
}

void toggle_mac_layer() {
  set_mac_layer( ! user_config.is_mac);
}

layer_state_t update_tri_layer_states(
  layer_state_t state,
  layer_state_t mask1,
  layer_state_t mask2,
  layer_state_t mask3
) {
  return (state & mask1) && (state & mask2) ? (state | mask3) : (state & ~mask3);
}

void tap_keycode(uint16_t keycode) {
  register_code(keycode);
  unregister_code(keycode);
}

char layer_state_str[16];

const char *get_layer_state_name(void) {
  switch(biton32(layer_state)) {
  case _QWERTY:
  case _COLEMAK:
  case _DVORAK:
    sprintf(layer_state_str, "Default");
    break;
  case _MAC:
    sprintf(layer_state_str, "Mac");
    break;
  // Temporary layers
  case _GAME:
    sprintf(layer_state_str, "Game");
    break;
  case _LOWER:
    sprintf(layer_state_str, "Lower");
    break;
  case _GAME_LOWER:
    sprintf(layer_state_str, "Game Lower");
    break;
  case _RAISE:
    sprintf(layer_state_str, "Raise");
    break;
  case _ADJUST:
    sprintf(layer_state_str, "Adjust");
    break;
  default:
    snprintf(layer_state_str, sizeof(layer_state_str), "Undef-%lx", layer_state);
    break;
  }

  return layer_state_str;
}