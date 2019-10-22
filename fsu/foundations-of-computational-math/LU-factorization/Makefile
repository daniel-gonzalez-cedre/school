all: a.out clean

a.out: main.o code.o matrix.o norms.o
	g++ -std="c++11" -o a.out main.o code.o matrix.o norms.o

main.o: main.cpp
	g++ -std="c++11" -c main.cpp

code.o: code.cpp
	g++ -std="c++11" -c code.cpp

matrix.o: matrix.cpp
	g++ -std="c++11" -c matrix.cpp

norms.o: norms.cpp
	g++ -std="c++11" -c norms.cpp

clean: 
	rm *.o
