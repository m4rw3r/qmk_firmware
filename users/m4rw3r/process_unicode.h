#ifndef PROCESS_UNICODE_H
#define PROCESS_UNICODE_H

#if defined(UNICODE_ENABLE) + defined(UNICODEMAP_ENABLE) + defined(UCIS_ENABLE) > 0
#    error "Cannot enable standard Unicode methods (UNICODE, UNICODEMAP, UCIS) while using a custom override"
#endif

#include "m4rw3r.h"

#ifndef UNICODE_KEY_MAC
#    define UNICODE_KEY_MAC KC_LALT
#endif
#ifndef UNICODE_KEY_LNX
#    define UNICODE_KEY_LNX LCTL(LSFT(KC_U))
#endif
#ifndef UNICODE_KEY_WINC
#    define UNICODE_KEY_WINC KC_RALT
#endif

// Delay between starting Unicode input and sending a sequence, in ms
#ifndef UNICODE_TYPE_DELAY
#    define UNICODE_TYPE_DELAY 10
#endif

#define X(i) (QK_UNICODEMAP | (i))
#define XP(i, j) (QK_UNICODEMAP_PAIR | ((i)&0x7F) | (((j)&0x7F) << 7))  // 127 max i and j

extern const uint32_t PROGMEM unicode_map[];

uint16_t unicodemap_index(uint16_t keycode);
bool process_unicode_keycode(uint16_t keycode, keyrecord_t *record);

#endif
