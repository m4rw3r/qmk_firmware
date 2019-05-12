#ifndef M4RW3R_H
#define M4RW3R_H

#include "quantum.h"
#include "version.h"
#include "process_records.h"
#include "config_common.h"

#ifdef AUDIO_ENABLE
#include "audio_stuff.h"
#endif

#ifdef RGBLIGHT_ENABLE
#include "rgb_stuff.h"
#endif

// Note: Important to populate all the layers in keymap.c
enum userspace_layers {
  // Persistent layers
  // Note: Must match the order of the keycodes used to switch to them
  _QWERTY = 0,
  _COLEMAK,
  _DVORAK,
  _MAC,
  // Temporary layers
  _GAME,
  _KEYPAD,
  _LOWER,
  _GAME_LOWER,
  _RAISE,
  _ADJUST
};

typedef union {
  uint32_t raw;
  struct {
    bool is_mac :1;
    bool use_rgb_layer_indicators :1;
  };
} user_config_t;

#define LAYER_MASK(layer) (1UL << (layer))

#define IS_LAYER_STATE_ON(state, layer) ((state) & LAYER_MASK(layer))
#define IS_LAYER_STATE_OFF(state, layer) (~(state) & LAYER_MASK(layer))

#define IS_LAYER_STATE_ACTIVATING(state, layer) IS_LAYER_OFF(layer) && IS_LAYER_STATE_ON(state, layer)
#define IS_LAYER_STATE_DEACTIVATING(state, layer) IS_LAYER_ON(layer) && IS_LAYER_STATE_OFF(state, layer)

#define LAYER_STATE_ACTIVATING(state) (layer_state ^ (state)) & (state)
#define LAYER_STATE_DEACTIVATING(state) (layer_state ^ (state)) & ~(state)

/**
 * Keymap version of process records, default to return true.
 */
bool process_record_keymap(uint16_t keycode, keyrecord_t *record);

/**
 * Keymap version of layer_state_set, callback called when layers are set.
 */
uint32_t layer_state_set_keymap(uint32_t state);

/**
 * Keymap version of keyboard_post_init_user.
 */
void keyboard_post_init_keymap(void);

/**
 * Keymap version of eeconfig_init_user.
 */
void eeconfig_init_keymap(void);

/**
 * Sets the Mac layer state and saves the configuration
 */
void set_mac_layer(bool enabled);

/**
 * Enables/disables the use of RGB lighting to indicate current layers.
 */
void set_rgb_layer_indicators(bool enabled);

/**
 * Toggles the Mac layer and saves the configuration
 */
void toggle_mac_layer(void);

void user_config_save(void);

/**
 * If one bit from each of mask1 and mask2 is set in state,
 * mask3 is applied to state, otherwise mask3 is removed from
 * state.
 */
uint32_t update_tri_layer_states(uint32_t state, uint32_t mask1, uint32_t mask2, uint32_t mask3);

/**
 * Taps the given keycode once.
 */
void tap_keycode(uint16_t keycode);

#endif