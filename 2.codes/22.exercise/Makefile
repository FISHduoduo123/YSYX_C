CFLAGS=-Wall -g -DNDEBUG

all: ex22_main

ex22_main: ex22_main.o ex22.o
	gcc $(CFLAGS) -o ex22_main ex22_main.o ex22.o

ex22_main.o: ex22_main.c ex22.h
	gcc $(CFLAGS) -c ex22_main.c 

ex22.o: ex22.c ex22.h
	gcc $(CFLAGS) -c ex22.c 

clean:
	rm -f ex22_main ex22.o