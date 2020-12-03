all: main.c reader.o rules.o sen_splitter.o
	gcc -Wall -g -std=gnu11 main.c reader.o rules.o sen_splitter.o -o program.out

reader.o: reader.h
	gcc -Wall -g -std=gnu11 -c reader.c

rules.o: rules.h
	gcc -Wall -g -std=gnu11 -c rules.c

sen_splitter.o: sen_splitter.h
	gcc -Wall -g -std=gnu11 -c sen_splitter.c
	
clean:
	rm -f *.o *.out

