LIB := ../../lib/spman.lib
all: $(LIB)

include ../../config.env

CC := sdcc
AR := sdar
CFLAGS := -mz80 --Werror -I../../include --fsigned-char --std-sdcc99 --opt-code-speed --fno-omit-frame-pointer $(EXTRA_CFLAGS)

SOURCES := $(wildcard *.c)
OBJS := $(patsubst %.c,%.rel,$(SOURCES))
CLEAN := $(patsubst %.c,%.asm,$(SOURCES)) $(patsubst %.c,%.lst,$(SOURCES)) $(patsubst %.c,%.sym,$(SOURCES)) \
	 $(OBJS) $(LIB)
$(LIB): $(OBJS)
	$(AR) -rcD $(LIB) $(OBJS)

%.rel: %.c
	$(CC) $(CFLAGS) -c $<

.PHONY: clean
clean:
	rm -f $(CLEAN)

