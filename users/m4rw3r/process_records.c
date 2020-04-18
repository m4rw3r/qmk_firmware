#include "process_records.h"

// Bootmagic config so we can check the WIN/ALT swap and determine how to send latin1 keys
extern user_config_t user_config;

const uint32_t PROGMEM unicode_map[] = {
  [U_AA] = 0x00E5,
  [U_AA_UC] = 0x00C5,
  [U_AE] = 0x00E4,
  [U_AE_UC] = 0x00C4,
  [U_OE] = 0x00F6,
  [U_OE_UC] = 0x00D6,
  [U_EUR] = 0x20AC,
};

// TODO: default_layer_state_set_user(state)

/**
 * Taps the given keycode.
 */
void tap_keycode(uint16_t keycode) {
  register_code(keycode);
  unregister_code(keycode);
}

/**
 * If one bit from each of mask1 and mask2 is set in state,
 * mask3 is applied to state, otherwise mask3 is removed from
 * state.
 */
layer_state_t update_tri_layer_states(
  layer_state_t state,
  layer_state_t mask_a,
  layer_state_t mask_b,
  layer_state_t mask_c
) {
  return (state & mask_a) && (state & mask_b) ? (state | mask_c) : (state & ~mask_c);
}

layer_state_t layer_state_set_user(layer_state_t state) {
  // Custom version of update_tri_layer_state to allow for deactivation while old state is held
  state = update_tri_layer_states(
    state,
    LAYER_MASK(_LOWER) | LAYER_MASK(_GAME_LOWER),
    LAYER_MASK(_RAISE),
    LAYER_MASK(_ADJUST));

  // Turn off Caps if we are leaving _GAME
  if(IS_LAYER_STATE_DEACTIVATING(state, _GAME) && IS_HOST_LED_ON(USB_LED_CAPS_LOCK)) {
    tap_keycode(KC_CAPS);
  }

  #ifdef AUDIO_ENABLE
  layer_state_set_audio(state);
  #endif

  #ifdef RGBLIGHT_ENABLE
  layer_state_set_rgb(state);
  #endif

  return layer_state_set_keymap(state);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch(keycode) {
  case KC_MAC:
    if(record->event.pressed) {
      set_host_os(OS_MAC);
    }

    return false;

  case KC_LNX:
    if(record->event.pressed) {
      set_host_os(OS_LNX);
    }

    return false;

  case KC_WIN:
    if(record->event.pressed) {
      set_host_os(OS_WIN);
    }

    return false;

  case KC_RGB_LAYER_INDICATORS:
    if(record->event.pressed) {
      set_rgb_layer_indicators(true);
    }

    return false;

  // For any of the RGB codes (see quantum_keycodes.h)
  case RGB_MODE_FORWARD ... RGB_HUD:
  // We skip RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD to allow changes to saturation
  // and brightness without turning off rgb layer indicators
  case RGB_SPI ... RGB_MODE_RGBTEST:
    if(record->event.pressed) {
      set_rgb_layer_indicators(false);
    }

    // Keep processing, we want these RGB changes to take effect
    return true;
  }

  return process_record_keymap(keycode, record);
};