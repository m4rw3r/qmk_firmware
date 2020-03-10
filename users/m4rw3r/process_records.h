#ifndef PROCESS_RECORDS_H
#define PROCESS_RECORDS_H

#include "m4rw3r.h"

#if defined(KEYMAP_SAFE_RANGE)
  #define USERSPACE_SAFE_RANGE KEYMAP_SAFE_RANGE
#else
  #define USERSPACE_SAFE_RANGE SAFE_RANGE
#endif

enum userspace_custom_keycodes {
  // Userspace toggles
  KC_MAC_OFF = USERSPACE_SAFE_RANGE,
  KC_MAC_ON,
  KC_RGB_LAYER_INDICATORS,
  // Swedish codes mapping to alt-codes or compose-sequences
  KX_AA,
  KX_AE,
  KX_OE,
  KX_EURO,
};

// Toggles Mac-layout layer
#define MAC_ON  KC_MAC_ON
#define MAC_OFF KC_MAC_OFF
#define RGBLAYER KC_RGB_LAYER_INDICATORS

#define GAME    TG(_GAME)
#define LOWER   MO(_LOWER)
#define G_LOWER MO(_GAME_LOWER)
#define RAISE   MO(_RAISE)

#define CTL_ESC LCTL_T(KC_ESC)
#define BK_LWER LT(_LOWER, KC_BSPC)
#define SP_LWER LT(_LOWER, KC_SPC)

#endif
