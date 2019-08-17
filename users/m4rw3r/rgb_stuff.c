#include "rgb_stuff.h"

extern user_config_t user_config;

uint8_t base_hue;
uint8_t base_mode;

/**
 * Sets the RGB lights to solid colour of given hue without modifying
 * brightness or saturation.
 */
void rgb_set_solid_hue(uint8_t hue) {
  rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
  rgblight_sethsv_noeeprom(hue, rgblight_get_sat(), rgblight_get_val());
}

void layer_state_set_rgb(layer_state_t state) {
  // Store base RGBlight settings, make sure to do this before we exit
  switch(biton32(layer_state)) {
  case _GAME:
  case _GAME_LOWER:
  case _RAISE:
  case _LOWER:
  case _ADJUST:
    // Do not save if we are not on a base-layer
    break;
  default:
    base_mode = rgblight_get_mode();
    base_hue  = rgblight_get_hue();
  }

  if( ! user_config.use_rgb_layer_indicators) {
    return;
  }

  switch(biton32(state)) {
  case _GAME:
    // Red
    rgb_set_solid_hue(0);
    break;
  case _RAISE:
    // Orange, matches button colour on Acute keycaps
    rgb_set_solid_hue(28);
    break;
  case _GAME_LOWER:
  case _LOWER:
    // Magenta, matches button colour on Acute keycaps
    rgb_set_solid_hue(213);
    break;
  case _ADJUST:
    // Green
    rgb_set_solid_hue(85);
    break;
  default:
    // Reset to user configuration, does not work
    rgblight_sethsv_noeeprom(base_hue, rgblight_get_sat(), rgblight_get_val());
    rgblight_mode_noeeprom(base_mode);
  }
}

void eeconfig_init_rgb(void) {
  rgblight_enable();
}