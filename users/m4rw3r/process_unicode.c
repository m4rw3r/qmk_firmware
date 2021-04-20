// We duplicate this funcitionality to enable decimal ALT-codes on windows to improve performance and compatibility

#include "process_unicode.h"

uint8_t unicode_saved_mods;

void unicode_input_start(void) {
  unicode_saved_mods = get_mods();  // Save current mods
  clear_mods();                     // Unregister mods to start from a clean state

  switch(get_host_os()) {
    case OS_MAC:
      register_code(UNICODE_KEY_MAC);

      break;

    case OS_LNX:
      tap_code16(UNICODE_KEY_LNX);

      break;

    case OS_WIN:
      register_code(KC_LALT);
      // We use cp1252, no plus

      break;
  }

  wait_ms(UNICODE_TYPE_DELAY);
}

void unicode_input_finish(void) {
  switch(get_host_os()) {
    case OS_MAC:
      unregister_code(UNICODE_KEY_MAC);
      break;

    case OS_LNX:
      tap_code(KC_SPC);
      break;

    case OS_WIN:
      unregister_code(KC_LALT);
      break;
  }

  set_mods(unicode_saved_mods);  // Reregister previously set mods
}

void unicode_input_cancel(void) {
  switch(get_host_os()) {
    case OS_MAC:
      unregister_code(UNICODE_KEY_MAC);

      break;

    case OS_LNX:
      tap_code(KC_ESC);

      break;
    case OS_WIN:
      unregister_code(KC_LALT);

      break;
  }

  set_mods(unicode_saved_mods);
}

uint16_t decimal_to_keypad(uint8_t hex) {
  if (hex == 0x0) {
    return KC_KP_0;
  }
  else {
    return KC_KP_1 + (hex - 0x1);
  }
}

void register_hex32(uint32_t hex) {
  bool onzerostart = true;

  for(int i = 7; i >= 0; i--) {
    if (i <= 3) {
      onzerostart = false;
    }

    uint8_t digit = ((hex >> (i * 4)) & 0xF);

    if(digit == 0) {
      if(!onzerostart) {
        send_nibble(digit);
      }
    }
    else {
      send_nibble(digit);
      onzerostart = false;
    }
  }
}

// Decimal input for cp1252
void register_cp1252(uint16_t code) {
  for(int i = 1000; i > 0; i /= 10) {
    int key = code / i;
    code = code % i;

    // Ensure we use the keypad
    tap_code(decimal_to_keypad(key));
  }
}

uint16_t unicodemap_index(uint16_t keycode) {
  if(keycode >= QK_UNICODEMAP_PAIR) {
    // Keycode is a pair: extract index based on Shift / Caps Lock state
    uint16_t index = keycode - QK_UNICODEMAP_PAIR;
    bool shift = unicode_saved_mods & MOD_MASK_SHIFT, caps = IS_HOST_LED_ON(USB_LED_CAPS_LOCK);

    if(shift ^ caps) {
      index >>= 7;
    }

    return index & 0x7F;
  }
  else {
    // Keycode is a regular index
    return keycode - QK_UNICODEMAP;
  }
}

bool process_unicode_keycode(uint16_t keycode, keyrecord_t *record) {
  if(keycode >= QK_UNICODEMAP && keycode <= QK_UNICODEMAP_PAIR_MAX && record->event.pressed) {
    unicode_input_start();

    uint32_t code = pgm_read_dword(unicode_map + unicodemap_index(keycode));
    HostOS  input_mode = get_host_os();

    // if(code > 0x10FFFF || (code > 0xFFFF && input_mode == OS_WIN)) {
    if(code > 0x10FFFF || (code > 0x00FF && input_mode == OS_WIN)) {
      // Character is out of range supported by the platform
      unicode_input_cancel();
    }
    else if (code > 0xFFFF && input_mode == OS_MAC) {
      // Convert to UTF-16 surrogate pair on Mac
      code -= 0x10000;
      uint32_t lo = code & 0x3FF, hi = (code & 0xFFC00) >> 10;
      register_hex32(hi + 0xD800);
      register_hex32(lo + 0xDC00);
      unicode_input_finish();
    }
    else if(input_mode == OS_WIN) {
      register_cp1252(code);
      unicode_input_finish();
    }
    else {
      register_hex32(code);
      unicode_input_finish();
    }
  }

  return true;
}
