CC = gcc
CFLAGS = -g -Wall -Wextra -pedantic -I$$RAYLIB_HOME/include
LDFLAGS = -L$$RAYLIB_HOME/lib -lraylib -lm -lX11

all: run

main: bagels.c
	$(CC) $^ $(CFLAGS) $(LDFLAGS)

debug: main
	gdb a.out

run: main
	./a.out

clean:
	rm -rf *.o *.out
