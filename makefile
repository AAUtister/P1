all: main.c reader.o rules.o
	gcc -Wall -g -std=gnu11 main.c reader.o rules.o -o program.out

reader.o: reader.h
	gcc-10 -Wall -g -std=gnu11 -c reader.c

rules.o: rules.h
	gcc-10 -Wall -g -std=gnu11 -c rules.c

rules.o: rules.h
	gcc -Wall -g -std=gnu11 -c rules.c

clean:
	rm -f *.o *.out

