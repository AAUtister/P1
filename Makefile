CC		= gcc
CFLAGS	= -Wall -g -std=gnu11
LDLIBS	= -lmxml
MXML = $(shell pwd)/lib/mxml-3.2
GTK = $(shell pwd)/lib/gt-3.0
GTK_FLAGS = -rdynamic -pthread -I/usr/include/at-spi2-atk/2.0 -I/usr/include/at-spi-2.0 -I/usr/include/dbus-1.0 -I/usr/lib/x86_64-linux-gnu/dbus-1.0/include -I/usr/include/gio-unix-2.0 -I/usr/include/cairo -I/usr/include/pango-1.0 -I/usr/include/fribidi -I/usr/include/harfbuzz -I/usr/include/atk-1.0 -I/usr/include/cairo -I/usr/include/pixman-1 -I/usr/include/uuid -I/usr/include/freetype2 -I/usr/include/libpng16 -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/libmount -I/usr/include/blkid -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include
GTK_LIBS = -lgtk-3 -lgdk-3 -lpangocairo-1.0 -lpango-1.0 -lharfbuzz -latk-1.0 -lcairo-gobject -lcairo -lgdk_pixbuf-2.0 -lgio-2.0 -lgobject-2.0 -lglib-2.0

##############################
#   Default Make Target      #
##############################
all: src/main.c reader.o rules.o minixml.o nexus.o src/utf8.h src/minixml.h src/word.h achievements.o
	$(CC) -o program.out $(GTK_FLAGS) $(CFLAGS) src/main.c reader.o nexus.o achievements.o rules.o minixml.o -I$(MXML)/include -L$(MXML)/lib -I$(GTK) $(LDLIBS) $(GTK_LIBS)

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
#   glib-2.9.6 Make Target  #
##############################
prepare: glib

glib: glib-config
	make -C lib/glib-2.9.6/ install
glib-config: glib-extract
	cd lib/glib-2.9.6 && ./configure --prefix=$(shell pwd)/lib/glib-2.9.6
glib-extract:
	tar -xvf glib-2.9.6.tar.gz -C lib/

##############################
#   atk-2.9.2 Make Target  #
##############################
prepare: atk

atk: atk-config
	make -C lib/atk-2.9.2/ install
atk-config: atk-extract
	cd lib/atk-2.9.2 && ./configure --prefix=$(shell pwd)/lib/atk-2.9.2
atk-extract:
	tar -xvf atk-2.9.2.tar.xz -C lib/

##############################
#   gdk-pixbuf-2.0 Make Target  #
##############################
prepare: gdk-pixbuf

gdk-pixbuf: gdk-pixbuf-config
	make -C lib/gdk-pixbuf-2.42.2/ install
gdk-pixbuf-config: gdk-pixbuf-extract
	cd lib/gdk-pixbuf-2.42.2 && ./configure --prefix=$(shell pwd)/lib/gdk-pixbuf-2.42.2
gdk-pixbuf-extract:
	tar -xvf gdk-pixbuf-2.42.2.tar.xz -C lib/

##############################
#   gobject-introspection-1.66.1 Make Target  #
##############################
prepare: gobject-introspection

gobject-introspection: gobject-introspection-config
	make -C lib/gobject-introspection-1.66.1/ install
gobject-introspection-config: gobject-introspection-extract
	cd lib/gobject-introspection-1.66.1 && ./configure --prefix=$(shell pwd)/lib/gobject-introspection-1.66.1
gobject-introspection-extract:
	tar -xvf gobject-introspection-1.66.1.tar.xz -C lib/

##############################
#   libepoxy-1.5.4 Make Target  #
##############################
prepare: libepoxy

libepoxy: libepoxy-config
	make -C lib/libepoxy-1.5.4/ install
libepoxy-config: libepoxy-extract
	cd lib/libepoxy-1.5.4 && ./configure --prefix=$(shell pwd)/lib/libepoxy-1.5.4
libepoxy-extract:
	tar -xvf libepoxy-1.5.4.tar.xz -C lib/

##############################
#   pango-1.9.1 Make Target  #
##############################
prepare: pango

pango: pango-config
	make -C lib/pango-1.9.1/ install
pango-config: pango-extract
	cd lib/pango-1.9.1 && ./configure --prefix=$(shell pwd)/lib/pango-1.9.1
pango-extract:
	tar -xvf pango-1.9.1.tar.gz -C lib/

##############################
#   gtk-3.0 Make Target  #
##############################
prepare: gtk

gtk: gtk-config
	make -C lib/gtk+-3.0.0/ install
gtk-config: gtk-extract
	cd lib/gtk+-3.0.0 && ./configure --prefix=$(shell pwd)/lib/gtk+-3.0.0
gtk-extract:
	tar -xvf gtk+-3.0.0.tar.gz -C lib/
##############################
#   Cleaning                 #
##############################
clean:
	rm -f *.o *.out output.txt
clean-libs:
	rm -r lib/mxml-3.2 mxml-3.2.tar.gz
	rm -r lib/gtk+-3.0.0 gtk+-3.0.0.tar.gz 
purge: clean clean-libs
