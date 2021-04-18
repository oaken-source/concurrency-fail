
BIN = concurrency

CFLAGS = -Wall -Wextra -g -pthread

SRC = concurrency.c \

all: $(BIN)

clean:
	$(RM) $(BIN)

$(BIN): $(SRC)
	$(CC) -o $@ $(CFLAGS) $^
