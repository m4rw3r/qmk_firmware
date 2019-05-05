#ifndef PROCESS_RECORDS_H
#define PROCESS_RECORDS_H

#include "m4rw3r.h"

#if defined(KEYMAP_SAFE_RANGE)
  #define USERSPACE_SAFE_RANGE KEYMAP_SAFE_RANGE
#else
  #define USERSPACE_SAFE_RANGE SAFE_RANGE
#endif

enum userspace_custom_keycodes {
  KC_QWERTY = USERSPACE_SAFE_RANGE,
  KC_COLEMAK,
  KC_DVORAK,
  // KC_GAME,
  // KC_KEYPAD,
  // KC_LOWER,
  // KC_RAISE,
  KC_BACKLIT,
  KX_AA,
  KX_AE,
  KX_OE,
  KX_EURO,
};

#define QWERTY  KC_QWERTY
#define COLEMAK KC_COLEMAK
#define DVORAK  KC_COLEMAK
#define BACKLIT KC_BACKLIT

#define KEYPAD  TG(_KEYPAD)
#define GAME    TG(_GAME)
#define LOWER   MO(_LOWER)
#define G_LOWER MO(_GAME_LOWER)
#define RAISE   MO(_RAISE)

#define BK_LWER LT(_LOWER, KC_BSPC)
#define SP_LWER LT(_LOWER, KC_SPC)

#endif
