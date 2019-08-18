
# If you want to change the display of OLED, you need to change here
SRC += ./lib/glcdfont.c \
       ./lib/rgb_state_reader.c \
       ./lib/logo_reader.c \
       #./lib/layer_state_reader.c \
       #./lib/keylogger.c \
       #./lib/mode_icon_reader.c \
       #./lib/host_led_state_reader.c \
       # ./lib/timelogger.c \

AUDIO_ENABLE = no
BACKLIGHT_ENABLE = no
BLUETOOTH_ENABLE = no
BOOTMAGIC_ENABLE = no
COMMAND_ENABLE = no
CONSOLE_ENABLE = no
EXTRAKEY_ENABLE = yes
MIDI_ENABLE = no
MOUSEKEY_ENABLE = no
NKRO_ENABLE = yes
RGBLIGHT_ENABLE = no
SWAP_HANDS_ENABLE = no
UNICODE_ENABLE = no

RGBLIGHT_STARTUP_ANIMATION = no
RGB_MATRIX_ENABLE = WS2812

SLEEP_LED_ENABLE = no

OLED_DRIVER_ENABLE = yes

# LTO to optimize away unused stuff
LINK_TIME_OPTIMIZATION_ENABLE = yes