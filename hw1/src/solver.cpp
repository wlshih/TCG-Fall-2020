/**
 * Theory of Computer Games Hw1
 * Usage: ./solver input_file [ > output_file ]
**/

#include <iostream>
#include <fstream>

//#include "solver.h"
#include "AStarSearch.h"


using namespace std;

int main(int argc, char **argv) {
	
	if(argc != 2) {
		cerr << "Usage ./solver input_file [ > output_file ]" << endl;
		return 1;
	}

	ifstream file;
	file.open(argv[1]);
	if(!file.is_open()) {
		cerr << "Error: input file " << argv[1] << " not found." << endl;
		return 1;
	}

	AStarSearch A;





	return 0;
}