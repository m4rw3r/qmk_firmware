SRC += m4rw3r.c \
       process_records.c

ifeq ($(strip $(AUDIO_ENABLE)), yes)
  SRC += audio_stuff.c
endif