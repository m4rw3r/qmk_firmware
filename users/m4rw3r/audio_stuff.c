#include "audio_stuff.h"

float game_on_song[][2]  = SONG(ONE_UP_SOUND);
float game_off_song[][2] = SONG(COIN_SOUND);
float keypad_on_song[][2]  = SONG(NUM_LOCK_ON_SOUND);
float keypad_off_song[][2] = SONG(NUM_LOCK_OFF_SOUND);

void layer_state_set_audio(uint32_t state) {
  switch(biton32(LAYER_STATE_ACTIVATING(state))) {
  case _GAME:
    return PLAY_SONG(game_on_song);
  case _KEYPAD:
    return PLAY_SONG(keypad_on_song);
  }

  switch(biton32(LAYER_STATE_DEACTIVATING(state))) {
  case _GAME:
    return PLAY_SONG(game_off_song);
  case _KEYPAD:
    return PLAY_SONG(keypad_off_song);
  }
}