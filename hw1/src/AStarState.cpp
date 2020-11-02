#include "AStarState.h"
#include <iostream>

using namespace std;

AStarState::AStarState(int n, int m, string board) {
	this->n = n;
	this->m = m;

	this->map.resize(n);
	for(auto i=0; i<n; i++) {
		for(auto j=0; j<m; j++) {
		this->map[i].resize(m);
			this->map[i][j] = board.at(i*m + j);
		}
	}
	// printBoard();
}


void AStarState::printBoard() {
	for(auto &row : this->map) {
		for(auto &c : row) cout << c;
		cout << endl;
	}
}

