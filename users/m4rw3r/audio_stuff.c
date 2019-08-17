#include "audio_stuff.h"

float game_on_song[][2]  = SONG(SCROLL_LOCK_ON_SOUND);
float game_off_song[][2] = SONG(SCROLL_LOCK_OFF_SOUND);
float mac_on_song[][2]  = SONG(AG_SWAP_SOUND);
float mac_off_song[][2] = SONG(AG_NORM_SOUND);

void layer_state_set_audio(layer_state_t state) {
  switch(biton32(LAYER_STATE_ACTIVATING(state))) {
  case _MAC:
    return PLAY_SONG(mac_on_song);
  case _GAME:
    return PLAY_SONG(game_on_song);
  }

  switch(biton32(LAYER_STATE_DEACTIVATING(state))) {
  case _MAC:
    return PLAY_SONG(mac_off_song);
  case _GAME:
    return PLAY_SONG(game_off_song);
  }
}