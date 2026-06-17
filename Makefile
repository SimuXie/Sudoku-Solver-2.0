CC = gcc
CFLAGS = -Iexternal/raylib -Iinclude
LDFLAGS = -Lexternal/raylib -lraylib -lm -lpthread -ldl -lrt -lX11
ASAN = -fsanitize=address -g -O1

SRC := $(wildcard src/*.c) $(wildcard src/sudoku/*.c) $(wildcard src/solvers/*.c) $(wildcard src/misc/*.c)
OUT = main.exe

all:
	$(CC) $(CFLAGS) $(SRC) -o $(OUT) $(LDFLAGS)

clean:
	rm $(OUT)