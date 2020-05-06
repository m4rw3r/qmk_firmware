SRC += m4rw3r.c \
       process_records.c \
       process_unicode.c

BACKLIGHT_ENABLE = no
BOOTMAGIC_ENABLE = lite
CONSOLE_ENABLE = no
MOUSEKEY_ENABLE = no
EXTRAKEY_ENABLE = yes # Required for media keys
MIDI_ENABLE = no
NKRO_ENABLE = no
UNICODE_ENABLE = no
UNICODEMAP_ENABLE = no
UCIS_ENABLE = no
SWAP_HANDS_ENABLE = no
RGBLIGHT_STARTUP_ANIMATION = no
SLEEP_LED_ENABLE = no

ifeq ($(strip $(AUDIO_ENABLE)), yes)
  SRC += audio_stuff.c
endif

ifeq ($(strip $(RGBLIGHT_ENABLE)), yes)
  SRC += rgb_stuff.c
endif

# LTO to optimize away unused stuff
LINK_TIME_OPTIMIZATION_ENABLE = yes