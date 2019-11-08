CC := gcc
CFLAGS := -g -Wall

SRC := src

NESTED_CALL = $(MAKE) -C $(SRC) CC="$(CC)" CFLAGS="$(CFLAGS)"

.PHONY: all testclient testserver testadmin

all: testclient testserver testadmin

testclient:
	$(NESTED_CALL) $@

testserver:
	$(NESTED_CALL) $@

testadmin:
	$(NESTED_CALL) $@
