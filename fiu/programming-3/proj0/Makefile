all: reverse clean

reverse: main.o partA.o partB.o partC.o
	gcc -o reverse main.o partA.o partB.o partC.o

main.o: main.c partA.h partB.h partC.h
	gcc -c main.c

partA.o: partA.c
	gcc -c partA.c

partB.o: partB.c
	gcc -c partB.c

partC.o: partC.c
	gcc -c partC.c

clean: 
	rm *.o
