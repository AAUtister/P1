CC		= gcc
CFLAG	= -Wall -g -std=gnu11
LDLIBS	=

all: src/main.c reader.o
	$(CC) -o program.out src/main.c reader.o

reader.o: src/reader.h
	$(CC) -c $(CFLAGS) src/reader.c

clean:
	rm -f *.o *.out output.txt
