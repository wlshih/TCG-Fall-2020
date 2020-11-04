CXX = g++ -std=c++11 -Wall -O3

all: clean src/solver.cpp
	$(CXX) src/*.cpp -c
	$(CXX) *.o -o solver
	rm -rf *.o

clean:
	rm -rf *.o || true

tiny: all
	./solver testdata/tiny.in

nano: all
	./solver testdata/nano.in
