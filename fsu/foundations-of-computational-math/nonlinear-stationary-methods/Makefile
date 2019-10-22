all: a.out clean

a.out: code.o norms.o linear-algebra.o
	g++ -std="c++11" -o a.out code.o norms.o linear-algebra.o

code.o: code.cpp
	g++ -std="c++11" -c code.cpp

norms.o: norms.cpp
	g++ -std="c++11" -c norms.cpp

linear-algebra.o: linear-algebra.cpp
	g++ -std="c++11" -c linear-algebra.cpp

clean: 
	rm *.o
