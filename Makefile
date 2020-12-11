CC		= gcc
CFLAGS	= -Wall -g -std=gnu11
LDLIBS	= -lmxml
MXML = $(shell pwd)/lib/mxml-3.2

all: src/main.c reader.o rules.o sen_splitter.o minixml.o src/utf8.h src/minixml.h src/word.h
	$(CC) -o program.out $(CFLAGS) src/main.c reader.o rules.o sen_splitter.o minixml.o -I$(MXML)/include -L$(MXML)/lib $(LDLIBS)

reader.o: src/reader.h
	$(CC) -c $(CFLAGS) src/reader.c

rules.o: src/rules.h src/utf8.h
	$(CC) -c $(CFLAGS) src/rules.c

sen_splitter.o: src/sen_splitter.h
	$(CC) -c $(CFLAGS) src/sen_splitter.c

minixml.o: src/minixml.h 
	$(CC) -c $(CFLAGS) src/minixml.c -I$(MXML)/include -L$(MXML)/lib $(LDLIBS)

# Compile & Run xml stuff only with `make minixml && ./minixml.out`
minixml: src/minixml.c reader.o src/word.h src/utf8.h mxml
	$(CC) -o minixml.out $(CFLAGS) src/minixml.c reader.o -I$(MXML)/include -L$(MXML)/lib $(LDLIBS)

clean:
	rm -f *.o *.out output.txt

#############################
#	Minixml-3.2 Make stuff	#
#############################
mxml: mxml-config
	make -C lib/mxml-3.2/ install
mxml-config: mxml-extract
	cd lib/mxml-3.2 && ./configure --prefix=$(shell pwd)/lib/mxml-3.2
mxml-extract:
	tar -xvf mxml-3.2.tar.gz -C lib/
clean-mxml:
	rm -r lib/mxml-3.2
