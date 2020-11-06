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


	AStarSearch *A;

	int n, m;
	while(cin >> n >> m) {
		// read data from stdin
		string line, board_data;
		for(auto i=n; i>0; i--) {
			cin >> line;
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