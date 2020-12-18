CC		= gcc
CFLAGS	= -Wall -g -std=gnu11
LDLIBS	= -lmxml
MXML = $(shell pwd)/lib/mxml-3.2

##############################
#   Default Make Target      #
##############################
all: src/main.c reader.o rules.o minixml.o nexus.o src/utf8.h src/minixml.h src/word.h achievements.o
	$(CC) -o program.out $(CFLAGS) src/main.c reader.o nexus.o achievements.o rules.o minixml.o -I$(MXML)/include -L$(MXML)/lib $(LDLIBS)

reader.o: src/reader.h
	$(CC) -c $(CFLAGS) src/reader.c

achievements.o: src/achievements.h
	$(CC) -c $(CFLAGS) src/achievements.c
	
nexus.o: src/nexus.h
	$(CC) -c $(CFLAGS) src/nexus.c

rules.o: src/rules.h src/utf8.h
	$(CC) -c $(CFLAGS) src/rules.c

minixml.o: src/minixml.h 
	$(CC) -c $(CFLAGS) src/minixml.c -I$(MXML)/include -L$(MXML)/lib $(LDLIBS)

##############################
#   Minixml-3.2 Make Target  #
##############################
prepare: mxml

mxml: mxml-config
	make -C lib/mxml-3.2/ install
mxml-config: mxml-extract
	cd lib/mxml-3.2 && ./configure --prefix=$(shell pwd)/lib/mxml-3.2
mxml-extract:
	tar -xvf mxml-3.2.tar.gz -C lib/

##############################
#   Cleaning                 #
##############################
clean:
	rm -f *.o *.out output.txt
clean-libs:
	rm -r lib/mxml-3.2 mxml-3.2.tar.gz savegame.csv
purge: clean clean-libs
