#ifndef M4RW3R_H
#define M4RW3R_H

#include "quantum.h"
#include "version.h"
#include "process_records.h"
#include "process_unicode.h"
#include "config_common.h"

// Note: Important to populate all the layers in keymap.c
enum userspace_layers {
  // Persistent layers
  // Note: Must match the order of the keycodes used to switch to them
  _BASE = 0,
  _MAC,
  // Temporary layers
  _GAME,
  _LOWER,
  _GAME_LOWER,
  _RAISE,
  _ADJUST
};

// The OS of the connected computer
//
// NOTE: Ensure it fits in the user_config_t field
typedef enum {
  OS_WIN = 0,
  OS_LNX = 1,
  OS_MAC = 2,
} HostOS;

typedef union {
  uint32_t raw;
  struct {
    HostOS host_os :2;
    bool use_rgb_layer_indicators :1;
  } data;
} user_config_t;

#define LAYER_MASK(layer) (1UL << (layer))

#define IS_LAYER_STATE_ON(state, layer) ((state) & LAYER_MASK(layer))
#define IS_LAYER_STATE_OFF(state, layer) (~(state) & LAYER_MASK(layer))

#define IS_LAYER_STATE_ACTIVATING(state, layer) IS_LAYER_OFF(layer) && IS_LAYER_STATE_ON(state, layer)
#define IS_LAYER_STATE_DEACTIVATING(state, layer) IS_LAYER_ON(layer) && IS_LAYER_STATE_OFF(state, layer)

#define LAYER_STATE_ACTIVATING(state) (layer_state ^ (state)) & (state)
#define LAYER_STATE_DEACTIVATING(state) (layer_state ^ (state)) & ~(state)

#ifdef AUDIO_ENABLE
#include "audio_stuff.h"
#endif

#ifdef RGBLIGHT_ENABLE
#include "rgb_stuff.h"
#endif

/**
 * Keymap version of process records, default to return true.
 */
bool process_record_keymap(uint16_t keycode, keyrecord_t *record);

/**
 * Keymap version of layer_state_set, callback called when layers are set.
 */
layer_state_t layer_state_set_keymap(layer_state_t state);

/**
 * Keymap version of keyboard_pre_init_user.
 */
void keyboard_pre_init_keymap(void);

/**
 * Keymap version of keyboard_post_init_user.
 */
void keyboard_post_init_keymap(void);

/**
 * Keymap version of eeconfig_init_user.
 */
void eeconfig_init_keymap(void);

/**
 * Keymap version of matrix_init_user.
 */
void matrix_init_keymap(void);

/**
 * Keymap version of matrix_scan_user.
 */
void matrix_scan_keymap(void);

/**
 * Sets the Host OS and saves the configuration
 */
void set_host_os(HostOS os);

HostOS get_host_os(void);

/**
 * Enables/disables the use of RGB lighting to indicate current layers.
 */
void set_rgb_layer_indicators(bool enabled);

void user_config_save(void);

/**
 * Reads the given layer and returns a user-readable layer name.
 */
const char *get_layer_state_name(void);

/**
 * Returns the current OS name.
 */
const char *get_os_name(void);

#endif