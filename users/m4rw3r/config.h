
// We want to be able to do ESC + LETTER quickly and get CTRL + LETTER instead
#define PERMISSIVE_HOLD
// We want to be able to do ESC : quickly, this will ignore the CTRL fucntion
// of ESC if we release it before we release the other button
#define IGNORE_MOD_TAP_INTERRUPT
// Speed up unicode input
#define UNICODE_TYPE_DELAY 0

// Global audio configuration
#ifdef AUDIO_ENABLE
  #define STARTUP_SONG SONG(PREONIC_SOUND)

  #define DEFAULT_LAYER_SONGS { SONG(QWERTY_SOUND), \
                                SONG(COLEMAK_SOUND), \
                                SONG(DVORAK_SOUND) \
                              }
#endif