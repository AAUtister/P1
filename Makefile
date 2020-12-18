CC		= gcc
CFLAGS	= -Wall -g -std=gnu11
LDLIBS	= -lmxml
MXML = $(shell pwd)/lib/mxml-3.2
GTK_FLAGS = -rdynamic -pthread -I/usr/include/gtk-3.0 -I/usr/include/at-spi2-atk/2.0 -I/usr/include/at-spi-2.0 -I/usr/include/dbus-1.0 -I/usr/lib/x86_64-linux-gnu/dbus-1.0/include -I/usr/include/gtk-3.0 -I/usr/include/gio-unix-2.0 -I/usr/include/cairo -I/usr/include/pango-1.0 -I/usr/include/fribidi -I/usr/include/harfbuzz -I/usr/include/atk-1.0 -I/usr/include/cairo -I/usr/include/pixman-1 -I/usr/include/uuid -I/usr/include/freetype2 -I/usr/include/libpng16 -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/libmount -I/usr/include/blkid -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include
GTK_LIBS = -lgtk-3 -lgdk-3 -lpangocairo-1.0 -lpango-1.0 -lharfbuzz -latk-1.0 -lcairo-gobject -lcairo -lgdk_pixbuf-2.0 -lgio-2.0 -lgobject-2.0 -lglib-2.0

##############################
#   Default Make Target      #
##############################
all: src/main.c reader.o rules.o minixml.o nexus.o src/utf8.h src/minixml.h src/word.h achievements.o
	$(CC) -o program.out $(CFLAGS) $(GTK_FLAGS) src/main.c reader.o nexus.o achievements.o rules.o minixml.o -I$(MXML)/include -L$(MXML)/lib $(GTK_LIBS) $(LDLIBS)

reader.o: src/reader.h
	$(CC) -c $(CFLAGS) src/reader.c

achievements.o: src/achievements.h
	$(CC) -c $(CFLAGS) src/achievements.cc
	
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
	rm -r lib/mxml-3.2 mxml-3.2.tar.gz
purge: clean clean-libs
