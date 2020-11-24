/**
 * Theory of Computer Games Hw1
 * Usage: ./solver [ stage_number ] < input_file > output_file
**/

#include <iostream>
#include <fstream>

//#include "solver.h"
#include "AStarSearch.h"


using namespace std;

int main(int argc, char **argv) {
	
	unsigned int n, m;
	unsigned int stage = 0;
	
	if(argc == 2) stage = stoi(argv[1]);

	AStarSearch *A;

	for(int i=1; cin >> n >> m; i++) {
		// read data from stdin
		string line, board_data;
		for(auto i=n; i>0; i--) {
			cin >> line;
			board_data.append(line);
		}
		// cout << board << endl;

		if(stage != i && stage != 0) continue;

		A = new AStarSearch(n, m, board_data);
		// perform search
		if(!A->search()) {
			cout << "\nSolution not found :(((" << endl;
		}

		delete A;
	}





	return 0;
}