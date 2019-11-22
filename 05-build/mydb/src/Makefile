SRC := .
INCLUDE := .
LIB := .

CLIENT_FILES := $(SRC)/testclient $(SRC)/client_comm
SERVER_FILES := $(SRC)/testserver $(SRC)/server_comm
ADMIN_FILES  := $(SRC)/testadmin

DATA_C_INCLUDES := defs.h error.h memory.h linklist.h strutil.h textfileio.h data.h

COMMON_FILES := $(patsubst %.c,%.o,$(filter-out $(addsuffix .c, $(CLIENT_FILES) $(SERVER_FILES) $(ADMIN_FILES)), $(wildcard $(SRC)/*.c)))

CC_COMMAND = $(CC) $(CFLAGS) -I$(INCLUDE) -o $@

.PHONY: all clean

all: testadmin testclient testserver

clean:
	$(RM) $(wildcard $(SRC)/*.o) $(LIB)/libmydb.a

testclient: $(SRC)/libmydb.a $(addsuffix .o, $(CLIENT_FILES))
	$(CC_COMMAND) $(addsuffix .o, $(CLIENT_FILES)) -L$(LIB) -lmydb -lreadline -lhistory

testserver: $(SRC)/libmydb.a $(addsuffix .o, $(SERVER_FILES))
	$(CC_COMMAND) $(addsuffix .o, $(SERVER_FILES)) -L$(LIB) -lmydb

testadmin: $(SRC)/libmydb.a $(addsuffix .o, $(ADMIN_FILES))
	$(CC_COMMAND) $(addsuffix .o, $(ADMIN_FILES)) -L$(LIB) -lmydb -lreadline -lhistory

data.o: data.c $(addprefix $(INCLUDE)/, $(DATA_C_INCLUDES))
	$(CC_COMMAND) -c $<

%.o: %.c
	$(CC_COMMAND) -c $<

libmydb.a: $(COMMON_FILES)
	ar -rcvs libmydb.a $(COMMON_FILES)