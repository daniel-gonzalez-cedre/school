all: nba clean

nba: main.o partA.o partB.o partC.o partD.o hash.o
	gcc -o nba main.o partA.o partB.o partC.o partD.o hash.o

main.o: main.c
	gcc -c main.c

partA.o: partA.c
	gcc -c partA.c

partB.o: partB.c
	gcc -c partB.c

partC.o: partC.c
	gcc -c partC.c

partD.o: partD.c
	gcc -c partD.c

hash.o: hash.c
	gcc -c hash.c

clean:
	rm *.o
