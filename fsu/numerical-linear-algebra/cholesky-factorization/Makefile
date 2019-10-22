all: a.out clean

a.out: code.o la.o
	g++ -std="c++11" -o a.out code.o la.o

code.o: code.cpp
	g++ -std="c++11" -c code.cpp

la.o: la.cpp
	g++ -std="c++11" -c la.cpp

clean: 
	rm *.o
