#include "audio_stuff.h"

float game_on_song[][2]  = SONG(AG_SWAP_SOUND);
float game_off_song[][2] = SONG(AG_NORM_SOUND);
float mac_song[][2]  = SONG(AG_SWAP_SOUND);
float windows_song[][2] = SONG(UNICODE_WINDOWS);
float linux_song[][2] = SONG(UNICODE_LINUX);

void play_os_song(HostOS os) {
  switch(os) {
  case OS_LNX:
    return PLAY_SONG(linux_song);
  case OS_MAC:
    return PLAY_SONG(mac_song);
  default:
    return PLAY_SONG(windows_song);
  }
}

void layer_state_set_audio(layer_state_t state) {
  switch(biton32(LAYER_STATE_ACTIVATING(state))) {
  case _GAME:
    return PLAY_SONG(game_on_song);
  }

  switch(biton32(LAYER_STATE_DEACTIVATING(state))) {
  case _GAME:
    return PLAY_SONG(game_off_song);
  }
}