#include "m4rw3r.h"
#include "eeprom.h"

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

void toggle_mac_layer() {
  set_mac_layer( ! user_config.is_mac);
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

/**
 * Applies layer mask `mask_c` if both `mask_a` and `mask_b` are matching at
 * least one layer each of the current layers, if at least one of them is not
 * enabled, `mask_c` is removed.
 */
layer_state_t update_tri_layer_states(
  layer_state_t state,
  layer_state_t mask_a,
  layer_state_t mask_b,
  layer_state_t mask_c
) {
  return (state & mask_a) && (state & mask_b) ? (state | mask_c) : (state & ~mask_c);
}

/**
 * Taps the given keycode.
 */
void tap_keycode(uint16_t keycode) {
  register_code(keycode);
  unregister_code(keycode);
}

/**
 * Returns a pointer to a static string containing the name for the currently
 * used layer.
 *
 * Not using a dynamic string to save some bytes to not include s[n]printf.
 */
const char *get_layer_state_name(void) {
  switch(biton32(layer_state)) {
  case _BASE:
    return "Default";
  case _MAC:
    return "Mac";
  // Temporary layers
  case _GAME:
    return "Game";
    break;
  case _LOWER:
    return "Lower";
    break;
  case _GAME_LOWER:
    return "Game Lower";
    break;
  case _RAISE:
    return "Raise";
    break;
  case _ADJUST:
    return "Adjust";
    break;
  default:
    return "Unknown";
  }
}