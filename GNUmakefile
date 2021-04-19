
BIN = concurrency

CFLAGS = -Wall -Wextra -g -pthread

SRC = concurrency.c thread_helper.c

all: $(BIN)

clean:
	$(RM) $(BIN)

$(BIN): $(SRC)
	$(CC) -o $@ $(CFLAGS) $^
