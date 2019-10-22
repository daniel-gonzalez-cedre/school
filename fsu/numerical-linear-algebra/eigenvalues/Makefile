all: a.out clean

a.out: code.o linear-algebra.o norms.o test-cases.o
	g++ -std="c++11" -o a.out code.o linear-algebra.o norms.o test-cases.o

code.o: code.cpp
	g++ -std="c++11" -c code.cpp

linear-algebra.o: linear-algebra.cpp
	g++ -std="c++11" -c linear-algebra.cpp

norms.o: norms.cpp
	g++ -std="c++11" -c norms.cpp

test-cases.o: test-cases.cpp
	g++ -std="c++11" -c test-cases.cpp

clean: 
	rm *.o
