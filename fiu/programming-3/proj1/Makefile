all: geometry clean

geometry: main.o partA.o partB.o partC.o partD.o
	gcc -o geometry main.o partA.o partB.o partC.o partD.o

main.o: main.c partA.h partB.h partC.h partD.h
	gcc -c main.c

partA.o: partA.c
	gcc -c partA.c

partB.o: partB.c
	gcc -c partB.c

partC.o: partC.c
	gcc -c partC.c

partD.o: partD.c
	gcc -c partD.c

clean:
	rm *.o
