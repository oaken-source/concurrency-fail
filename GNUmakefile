
# this Makefile is used by GNU make when compiling on Linux and MacOS

BIN = concurrency
OBJ = concurrency.o thread_helper.o

CFLAGS = -pthread -Wall -Wextra -g
LDFLAGS = -pthread

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) -o $@ $(LDFLAGS) $^

clean:
	$(RM) $(BIN) $(OBJ)
