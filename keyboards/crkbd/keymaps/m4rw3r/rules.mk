
# If you want to change the display of OLED, you need to change here
SRC += ./lib/glcdfont.c \
       ./lib/logo_reader.c \
       #./lib/rgb_state_reader.c \
       #./lib/layer_state_reader.c \
       #./lib/keylogger.c \
       #./lib/mode_icon_reader.c \
       #./lib/host_led_state_reader.c \
       # ./lib/timelogger.c \

AUDIO_ENABLE = no
BLUETOOTH_ENABLE = no
COMMAND_ENABLE = no
RGBLIGHT_ENABLE = no
RGB_MATRIX_ENABLE = WS2812
OLED_DRIVER_ENABLE = yes