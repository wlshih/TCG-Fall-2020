CXX = g++ -std=c++11 -Wall -O3

all: clean src/solver.cpp
	$(CXX) src/*.cpp -c
	$(CXX) *.o -o solver

clean:
	rm -rf *.o || true

small: all
	./solver < testdata/small.in

tiny: all
	./solver < testdata/tiny.in

nano: all
	./solver < testdata/nano.in

