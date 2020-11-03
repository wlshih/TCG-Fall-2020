#include "AStarState.h"
#include <iostream>
#include <string>

using namespace std;

AStarState::AStarState(int n, int m, BoardData data) {
	this->n = n;
	this->m = m;
	this->loadBoard(data);
	// printBoard();
}

// load data to the vector
void AStarState::loadBoard(BoardData data) {
	this->data = data;

	this->board.resize(n);
	for(auto i=0; i<n; i++) {
		for(auto j=0; j<m; j++) {
		this->board[i].resize(m);
			this->board[i][j] = data.at(i*m + j);
		}
	}
}

void AStarState::printBoard() {
	for(auto &row : this->board) {
		for(auto &c : row) cout << c;
		cout << endl;
	}
}

// encode board vector before pushing on closed list
State AStarState::encode() {
	State s;
	for(auto &row : this->board) {
		for(auto &c : row) {
			s += c;
		}
	}

	return s;
}

// store to board vector from the closed list
void AStarState::decode(State s) {
	loadBoard(s);
}


int AStarState::heuristic() {
	return 0;
}

bool AStarState::isEnd() {
	return 0;
}