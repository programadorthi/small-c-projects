OS_NAME := $(shell uname -s)

CC = gcc
DB = gdb
CFLAGS = -g -Wall -Wextra -pedantic -std=c11 -I$$RAYLIB_HOME/include
LDFLAGS = -L$$RAYLIB_HOME/lib -lraylib

ifeq ($(OS_NAME),Linux)
	LDFLAGS += -lm -lX11
endif

ifeq ($(OS_NAME),Darwin)
	CC = clang
	DB = lldb
	LDFLAGS += -framework OpenGL -framework Cocoa -framework IOKit -framework CoreAudio -framework CoreVideo
endif

all: run

main: bagels.c
	$(CC) $^ $(CFLAGS) $(LDFLAGS)

debug: main
	$(DB) a.out

run: main
	./a.out

clean:
	rm -rf *.o *.out
