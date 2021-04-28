
# this Makefile is used by nmake when compiling on windows

BIN = concurrency.exe
OBJ = concurrency.obj thread_helper.obj

all: $(BIN)

$(BIN): $(OBJ)
	link $(LFLAGS) $** /out:concurrency.exe

clean:
	-del $(BIN) $(OBJ)
