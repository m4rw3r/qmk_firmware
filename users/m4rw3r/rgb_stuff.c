#include "rgb_stuff.h"

void layer_state_set_rgb(uint32_t state) {
  // FIXME: Set colours
  switch(biton32(state)) {
  case _GAME:
  case _RAISE:
  case _GAME_LOWER:
  case _LOWER:
  case _ADJUST:
  case _MAC:
  case _KEYPAD:
    break;
  }
}

void eeconfig_init_rgb(void) {
  // rgblight_enable_noeeprom();
  // TODO: Update stuff according to layers
}