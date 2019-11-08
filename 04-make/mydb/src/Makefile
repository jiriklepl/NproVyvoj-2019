SRC := .
INCLUDE := .
LIB := .

.PHONY: all

testclient: $(SRC)/libmydb.a $(SRC)/testclient.o $(SRC)/client_comm.o
	$(CC) $(CFLAGS) -I$(INCLUDE) -L$(LIB) -lmydb -lreadline -lhistory -o $@ $(SRC)/testclient.o $(SRC)/client_comm.o

testserver: $(SRC)/libmydb.a $(SRC)/testserver.o $(SRC)/server_comm.o
	$(CC) $(CFLAGS) -I$(INCLUDE) -L$(LIB) -lmydb -o $@ $(SRC)/testserver.o $(SRC)/server_comm.o

testadmin: $(SRC)/libmydb.a $(SRC)/testadmin.o
	$(CC) $(CXX_FLAGS) -I$(INCLUDE) -L$(LIB) -lmydb -lreadline -lhistory -o $@ $(SRC)/testadmin.o

%.o: %.c
	$(CC) $(CFLAGS) -c -I$(INCLUDE) -o $@ $<

libmydb.a: 
	ar -rcvs libmydb.a