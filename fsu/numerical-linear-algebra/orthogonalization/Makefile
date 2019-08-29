all: a.out clean

a.out: code.o linear_algebra.o norms.o
	g++ -std="c++11" -o a.out code.o linear_algebra.o norms.o

code.o: code.cpp
	g++ -std="c++11" -c code.cpp

linear_algebra.o: linear_algebra.cpp
	g++ -std="c++11" -c linear_algebra.cpp

norms.o: norms.cpp
	g++ -std="c++11" -c norms.cpp

clean: 
	rm *.o
