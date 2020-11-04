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

	AStarSearch *A;

	int n, m;
	while(file >> n >> m) {
		// load data from file
		string line, board_data;
		for(auto i=n; i>0; i--) {
			file >> line;
			board_data.append(line);
		}
		// cout << board << endl;
		A = new AStarSearch(n, m, board_data);

		// perform search
		A->search();


		delete A;
	}





	return 0;
}