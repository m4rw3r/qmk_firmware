SRC += muse.c
# LTO to optimize away unused stuff
LINK_TIME_OPTIMIZATION_ENABLE = yes
# My Planck has WS2812B LEDs mounted on the pads
RGBLIGHT_ENABLE = yes