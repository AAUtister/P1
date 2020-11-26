all: main.c reader.o nexus.o
	gcc -Wall -g -std=gnu11 main.c reader.o nexus.o -o program.out

reader.o: reader.h
	gcc-10 -Wall -g -std=gnu11 -c reader.c

nexus.o: nexus.h
	gcc-10 -Wall -g -std=gnu11 -c nexus.c

clean:
	rm -f *.o *.out

