all: mycipher purge

mycipher: mycipher.o
	gcc -o mycipher mycipher.o

mycipher.o: mycipher.c
	gcc -c mycipher.c

purge:
	rm -f *.o

clean:
	rm -f *.o
	rm mycipher
