CC=clang
CFLAGS=
WFLAGS=-Weverything
LDFLAGS=-lm

default: build

update:
	git remote add -f snow https://github.com/mortie/snow
	git fetch snow master
	git subtree pull --prefix lib/snow snow master

build:
	$(CC) $(WFLAGS) -DSOL_N_GNU src/sol.h
	$(CC) $(WFLAGS) -DSOL_GNU src/sol.h
	$(CC) $(WFLAGS) -DSOL_GNU -mavx src/sol.h

test:
	$(CC) $(CFLAGS) -Og -fno-omit-frame-pointer -fsanitize=undefined tests/test.c -L. -L./src -I. -Ilib/snow -DSNOW_ENABLED -g -o test.o $(LDFLAGS)
	-@./test.o
	-@rm -rf *.o

clean:
	-@rm -rf *.gch *.o src/*.gch src/*.o
