OS_NAME := $(shell uname -s)

CC = gcc
DB = gdb
CFLAGS = -g -Wall -Wextra -pedantic -std=c11
OUTPUT = a.out

ifeq ($(OS_NAME),Windows_NT)
	CFLAGS += -I"$(RAYLIB_HOME)\include"
	LDFLAGS = -L"$(RAYLIB_HOME)\lib" -lraylib -lgdi32 -lwinmm
	OUTPUT = a.exe
else
	CFLAGS += -I$$RAYLIB_HOME/include
	LDFLAGS = -L$$RAYLIB_HOME/lib -lraylib
	ifeq ($(OS_NAME),Linux)
		LDFLAGS += -lm -lX11
	endif

	ifeq ($(OS_NAME),Darwin)
		CC = clang
		DB = lldb
		LDFLAGS += -framework OpenGL -framework Cocoa -framework IOKit -framework CoreAudio -framework CoreVideo
	endif
endif

all: run

main: bagels.c
	$(CC) $^ $(CFLAGS) $(LDFLAGS)

debug: main
	$(DB) $(OUTPUT)

run: main
	./$(OUTPUT)

clean:
	rm -rf *.o *.out *.exe
