all: main.c reader.o
	gcc -Wall -g -std=gnu11 main.c reader.o -o program.out

reader.o: reader.h
	gcc -Wall -g -std=gnu11 -c reader.c

clean:
	rm -f *.o *.out

