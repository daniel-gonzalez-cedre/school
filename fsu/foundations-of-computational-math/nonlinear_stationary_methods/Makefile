all: a.out clean

a.out: code.o norms.o linear_algebra.o
	g++ -std="c++11" -o a.out code.o norms.o linear_algebra.o

code.o: code.cpp
	g++ -std="c++11" -c code.cpp

norms.o: norms.cpp
	g++ -std="c++11" -c norms.cpp

linear_algebra.o: linear_algebra.cpp
	g++ -std="c++11" -c linear_algebra.cpp

clean: 
	rm *.o
