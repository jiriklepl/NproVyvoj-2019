CXX      := g++

CXX_FLAGS := 

BIN      := bin
SRC      := src
INCLUDE  := include

COMMON_FILES = $(patsubst %.cpp,%.o,$(wildcard $(SRC)/tcp-*) $(wildcard $(SRC)/udp-*))

.PHONY: all clean server client

all: server client

server: $(BIN)/server 

client: $(BIN)/client

clean:
	rm -f $(wildcard $(BIN)/*)
	rm -f $(wildcard $(SRC)/*.o)

%.o: %.cpp $(INCLUDE)
	$(CXX) -c $(CXX_FLAGS) -I$(INCLUDE) -o $@ $<

$(BIN)/server: $(COMMON_FILES) $(SRC)/server.o
	$(CXX) -I$(INCLUDE) -o $@ $^ 

$(BIN)/client: $(COMMON_FILES) $(SRC)/client.o
	$(CXX) -I$(INCLUDE) -o $@ $^
