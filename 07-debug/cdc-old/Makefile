
CFLAGS := -O0 -g
LDFLAGS := -lm

SOURCES := $(wildcard src/*.c)
OBJECTS := $(SOURCES:.c=.o)
DEPENDENCIES := $(SOURCES:.c=.d)

all: cd

include $(DEPENDENCIES)

cd: $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $^

%.d: %.c
	$(CC) -MM -MT '$*.o $*.d' $< > $@

clean: distclean
	rm -f cd
	
distclean:
	rm -f $(OBJECTS) $(DEPENDENCIES)
	
info:
	@echo
	@echo "SOURCES = $(SOURCES)"
	@echo "OBJECTS = $(OBJECTS)"
	@echo "DEPENDENCIES = $(DEPENDENCIES)"

	@echo
	@echo "CC = $(CC)"
	@echo "CFLAGS = $(CFLAGS)"
	
