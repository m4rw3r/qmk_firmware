#ifndef PROCESS_RECORDS_H
#define PROCESS_RECORDS_H

#include "m4rw3r.h"

#if defined(KEYMAP_SAFE_RANGE)
  #define USERSPACE_SAFE_RANGE KEYMAP_SAFE_RANGE
#else
  #define USERSPACE_SAFE_RANGE SAFE_RANGE
#endif

enum userspace_custom_keycodes {
  // From unicodemap support in quantum_keycodes.h
  QK_UNICODEMAP          = 0x8000,
  QK_UNICODEMAP_MAX      = 0xBFFF,
  QK_UNICODEMAP_PAIR     = 0xC000,
  QK_UNICODEMAP_PAIR_MAX = 0xFFFF,
  // Userspace toggles
  KC_WIN = USERSPACE_SAFE_RANGE,
  KC_MAC,
  KC_LNX,
  KC_RGB_LAYER_INDICATORS,
};

// Unicode characters defined in process_records.c
enum unicode_names {
  U_AA,
  U_AA_UC,
  U_AE,
  U_AE_UC,
  U_OE,
  U_OE_UC,
  U_EUR,
};

#define RGBLAYER KC_RGB_LAYER_INDICATORS

#define GAME    TG(_GAME)
#define LOWER   MO(_LOWER)
#define G_LOWER MO(_GAME_LOWER)
#define RAISE   MO(_RAISE)

#define CTL_ESC LCTL_T(KC_ESC)
#define BK_LWER LT(_LOWER, KC_BSPC)
#define SP_LWER LT(_LOWER, KC_SPC)

// Swedish
#define KX_AA XP(U_AA, U_AA_UC)
#define KX_AE XP(U_AE, U_AE_UC)
#define KX_OE XP(U_OE, U_OE_UC)
#define KX_EURO X(U_EUR)

#endif
