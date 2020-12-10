CC		= gcc
CFLAGS	= -Wall -g -std=gnu11
LDLIBS	= -lmxml

all: src/main.c reader.o rules.o sen_splitter.o
	$(CC) -o program.out $(CFLAGS) src/main.c reader.o rules.o sen_splitter.o

reader.o: src/reader.h
	$(CC) -c $(CFLAGS) src/reader.c

rules.o: src/rules.h
	$(CC) -c $(CFLAGS) src/rules.c

sen_splitter.o: src/sen_splitter.h
	$(CC) -c $(CFLAGS) src/sen_splitter.c
# Compile & Run xml stuff only with `make minixml && ./minixml.out`
minixml: src/minixml.c reader.o src/word.h src/utf8.h
	$(CC) -o minixml.out $(CFLAGS) src/minixml.c reader.o $(LDLIBS)

clean:
	rm -f *.o *.out output.txt
