CXX = g++ -std=c++11 -Wall -O3

all: clean src/solver.cpp
	$(CXX) src/*.cpp -c
	$(CXX) *.o -o solver
	rm -rf *.o

clean:
	rm -rf *.o solver || true

run: all
	./solver testdata/tiny.in
