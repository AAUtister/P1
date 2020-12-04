CC		= gcc
CFLAG	= -Wall -g -std=gnu11
LDLIBS	= -lmxml

all: src/main.c reader.o
	$(CC) -o program.out src/main.c reader.o

reader.o: src/reader.h
	$(CC) -c $(CFLAGS) src/reader.c

# Compile & Run xml stuff only with `make minixml && ./minixml.out`
minixml: src/minixml.c reader.o src/word.h src/utf8.h
	$(CC) -o minixml.out $(CFLAGS) src/minixml.c reader.o $(LDLIBS)

clean:
	rm -f *.o *.out output.txt
