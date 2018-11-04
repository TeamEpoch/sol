CC=cc
CFLAGS=
LDFLAGS=-lm

default: build

build:
	$(CC) $(CFLAGS) -c src/sol.h $(LDFLAGS)

clean:
	-@rm -rf *.gch *.o
