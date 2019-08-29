all: a.out clean

a.out: code.o linear_algebra.o norms.o test_cases.o
	g++ -std="c++11" -o a.out code.o linear_algebra.o norms.o test_cases.o

code.o: code.cpp
	g++ -std="c++11" -c code.cpp

linear_algebra.o: linear_algebra.cpp
	g++ -std="c++11" -c linear_algebra.cpp

norms.o: norms.cpp
	g++ -std="c++11" -c norms.cpp

test_cases.o: test_cases.cpp
	g++ -std="c++11" -c test_cases.cpp

clean: 
	rm *.o
