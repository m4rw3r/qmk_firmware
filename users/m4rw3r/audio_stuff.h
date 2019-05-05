#ifndef AUDIO_STUFF_H
#define AUDIO_STUFF_H

#include "m4rw3r.h"
#include "audio.h"

#define STARTUP_SONG SONG(PREONIC_SOUND)

#define DEFAULT_LAYER_SONGS { SONG(QWERTY_SOUND), \
                                SONG(COLEMAK_SOUND), \
                                SONG(DVORAK_SOUND) \
                            }

void layer_state_play_audio(uint32_t state);

#endif