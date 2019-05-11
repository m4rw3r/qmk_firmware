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
uint32_t layer_state_set_keymap(uint32_t state) {
  return state;
}

// Default implementation
__attribute__((weak))
void keyboard_post_init_keymap(void) { }

// Default implementation
__attribute__((weak))
void eeconfig_init_keymap(void) { }

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

uint32_t update_tri_layer_states(uint32_t state, uint32_t mask1, uint32_t mask2, uint32_t mask3) {
  return (state & mask1) && (state & mask2) ? (state | mask3) : (state & ~mask3);
}

void tap_keycode(uint16_t keycode) {
  register_code(keycode);
  unregister_code(keycode);
}