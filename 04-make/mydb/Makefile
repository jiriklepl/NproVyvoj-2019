CC := gcc
CFLAGS := -g -Wall

SRC := src

NESTED_CALL = $(MAKE) -C $(SRC) CC="$(CC)" CFLAGS="$(CFLAGS)"

.PHONY: all testclient testserver testadmin clean

all clean testclient testserver testadmin:
	$(NESTED_CALL) $@
