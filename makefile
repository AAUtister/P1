all: main.c txt-read.o verb-read.o
	gcc -Wall -g -std=gnu11 main.c txt-read.o verb-read.o -o program.out

txt-read.o: txt-read.h
	gcc -Wall -g -std=gnu11 -c txt-read.c

verb-read.o: verb-read.h
	gcc -Wall -g -std=gnu11 -c verb-read.c

clean:
	rm -f *.o *.out

