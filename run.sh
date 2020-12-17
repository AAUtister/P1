#!/bin/bash
if [[ ! -f mxml-3.2.tar.gz ]]; then
    echo "Mangler Mini-XML Bibliotek"
    echo "Downloader nu..."
    curl -L -O https://github.com/michaelrsweet/mxml/releases/download/v3.2/mxml-3.2.tar.gz
fi

if [[ ! -f lib/mxml-3.2/include/mxml.h ]]; then
    [ -d lib ] || mkdir lib
    echo "Mini-XML er ikke konfigureret"
    echo "Konfigurere Mini-XML nu..."
    make prepare
fi

if [[ ! -f program.out ]]; then
    echo "Programmet er ikke kompileret"
    echo "Kompilerer programmet nu..."
    make all
fi
LD_LIBRARY_PATH=lib/mxml-3.2 ./program.out
