SRC := .
INCLUDE := .
LIB := .

CLIENT_FILES := $(SRC)/testclient $(SRC)/client_comm
SERVER_FILES := $(SRC)/testserver $(SRC)/server_comm
ADMIN_FILES  := $(SRC)/testadmin

COMMON_FILES := $(patsubst %.c,%.o,$(filter-out $(addsuffix .c, $(CLIENT_FILES) $(SERVER_FILES) $(ADMIN_FILES)), $(wildcard $(SRC)/*.c)))

.PHONY: all clean

all: testadmin testclient testserver

clean:
	$(RM) $(wildcard $(SRC)/*.o) $(LIB)/libmydb.a

testclient: $(SRC)/libmydb.a $(addsuffix .o, $(CLIENT_FILES))
	$(CC) $(CFLAGS) -I$(INCLUDE) -o $@ $(addsuffix .o, $(CLIENT_FILES)) -L$(LIB) -lmydb -lreadline -lhistory

testserver: $(SRC)/libmydb.a $(addsuffix .o, $(SERVER_FILES))
	$(CC) $(CFLAGS) -I$(INCLUDE) -o $@ $(addsuffix .o, $(SERVER_FILES)) -L$(LIB) -lmydb

testadmin: $(SRC)/libmydb.a $(addsuffix .o, $(ADMIN_FILES))
	$(CC) $(CXX_FLAGS) -I$(INCLUDE) -o $@ $(addsuffix .o, $(ADMIN_FILES)) -L$(LIB) -lmydb -lreadline -lhistory

%.o: %.c
	$(CC) $(CFLAGS) -c -I$(INCLUDE) -o $@ $<

libmydb.a: $(COMMON_FILES)
	ar -rcvs libmydb.a $(COMMON_FILES)