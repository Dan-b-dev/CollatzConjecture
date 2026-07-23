CC = C:/msys64/ucrt64/bin/gcc.exe

CFLAGS = -std=c23 -Wall -Wextra -Wpedantic -O3 -march=native -Iinclude

SRC = $(wildcard src/*.c)

TARGET = collatz.exe

all:
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)