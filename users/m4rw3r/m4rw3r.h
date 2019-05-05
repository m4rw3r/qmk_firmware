#ifndef M4RW3R_H
#define M4RW3R_H

#include "quantum.h"
#include "version.h"
#include "process_records.h"
#include "config_common.h"

#ifdef AUDIO_ENABLE
#include "audio_stuff.h"
#endif

enum userspace_layers {
  _QWERTY = 0,
  _COLEMAK,
  _DVORAK,
  _GAME,
  _KEYPAD,
  _GAME_LOWER,
  _LOWER,
  _RAISE,
  _ADJUST
};

// #define IS_USB_LED_ON(led) host_keyboard_leds() & (1 << USB_LED_CAPS_LOCK)

#define IS_LAYER_STATE_ON(state, layer) ((state) & (1UL << (layer)))
#define IS_LAYER_STATE_OFF(state, layer) (~(state) & (1UL << (layer)))

#define IS_LAYER_STATE_ACTIVATING(state, layer) IS_LAYER_OFF(layer) && IS_LAYER_STATE_ON(state, layer)
#define IS_LAYER_STATE_DEACTIVATING(state, layer) IS_LAYER_ON(layer) && IS_LAYER_STATE_OFF(state, layer)

#define LAYER_STATE_ACTIVATING(state) (layer_state ^ (state)) & (state)
#define LAYER_STATE_DEACTIVATING(state) (layer_state ^ (state)) & layer_state

// Keymap version of process records, default to return true
bool process_record_keymap(uint16_t keycode, keyrecord_t *record);
// Keymap version of layer_state_set
uint32_t layer_state_set_keymap(uint32_t state);

#endif