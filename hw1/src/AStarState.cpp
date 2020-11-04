#include "AStarState.h"
#include <iostream>
#include <string>

using namespace std;

// load to board vector + encode to state key
AStarState::AStarState(int n, int m, BoardData data) {
	this->n = n;
	this->m = m;
	this->key = encode();
	this->loadBoard(data);
	// printBoard();
}

// load data to the vector, locate player position
void AStarState::loadBoard(BoardData data) {
	// this->data = data;

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
// store to this->key
StateKey AStarState::encode() {
	StateKey k; // same as BoardData currently
	for(auto &row : this->board) {
		for(auto &c : row) {
			k += c;
		}
	}
	this->key = k;

	return k;
}

// call this everytime you use a board from closed list
// autoload to board vector from the key stored on closed list
void AStarState::decode(StateKey k) {
	loadBoard(k);
}

int AStarState::heuristic() {
	return 0;
}

/*^^^^^^^^^^^^^^^^^^^^^^^^ state attributes ^^^^^^^^^^^^^^^^^^^^^^^*/
/*vvvvvvvvvvvvvvvvvvvvvvvvv gameplay rules vvvvvvvvvvvvvvvvvvvvvvvv*/

// update AStarState board vector after the move, return false if the move is invalid
bool AStarState::nextMove(Direction next) { // 1-byte unsigned char
	int next_px = px + dx(next);
	int next_py = py + dy(next);

	if(!isValid(next_px, next_py)) return false;

	// push items
	char next_blk = board[next_px][next_py];
	if((next_blk == BLK_BOX || next_blk == BLK_STAR) && !pushBox(next_px, next_py)) return false;
	else if(next_blk == BLK_BALL && !slideBall(next_px, next_py)) return false;
	
	// move player
	movePlayer(next_px, next_py);

	// StateKey is not updated!!!!

	return true;
}

int AStarState::dx(Direction D) {
	D &= MOV_MASK;
	switch(D) {
		case MOV_UP:
			return -1;
		case MOV_DOWN:
			return 1;
		default:
			return 0;
	}
}
int AStarState::dy(Direction D) {
	D &= MOV_MASK;
	switch(D) {
		case MOV_LEFT:
			return -1;
		case MOV_RIGHT:
			return 1;
		default:
			return 0;
	}
}

// only consider the boundaries and the walls
bool AStarState::isValid(int nx, int ny) {
	if(nx < 0 || ny < 0 || nx >= n || ny >= m) return false;
	if(board[nx][ny] == BLK_WALL) return false;
	return true;
}

// also consider boxes, stars, balls
bool AStarState::isValid(int nx, int ny, char item) {
	if(!isValid(nx, ny)) return false;
	if(item == BLK_BOX || item == BLK_STAR) {
		if(board[nx][ny] == BLK_BOX || board[nx][ny] == BLK_STAR) return false;
	}
	else if(item == BLK_BALL) {
		if(board[nx][ny] == BLK_BALL) return false;
	}

	return true;
}

// push boxes or stars
// from_x, from_y means player's NEW location, item's current position
bool AStarState::pushBox(int from_x, int from_y) {
	// box' location after pushing
	int to_x = (from_x << 1) - px;
	int to_y = (from_y << 1) - py;
	bool starBox = (board[from_x][from_y] == BLK_STAR);

	if(!isValid(to_x, to_y, BLK_BOX)) return false;
	// merge star
	if(!starBox && board[to_x][to_y] == BLK_BALL) {
		board[to_x][to_y] = BLK_STAR;
	}
	else {
		board[to_x][to_y] = board[from_x][from_y];
	}
	board[from_x][from_y] = BLK_PLAYER;
	board[px][py] = BLK_FLOOR;

	px = from_x;
	py = from_y;

	// add penalty

	return true;
}

// slide balls
bool AStarState::slideBall(int from_x, int from_y) {
	// ball's moving direction
	int _dx = from_x - px;
	int _dy = from_y - py;

	int to_x = from_x + _dx;
	int to_y = from_y + _dy;
	
	if(!isValid(to_x, to_y)) return false;

	while(board[to_x+_dx][to_y+_dy] == BLK_FLOOR) {
		to_x += _dx;
		to_y += _dy;
	}
	// merge star
	if(board[to_x][to_y] == BLK_BOX) {
		board[to_x][to_y] = BLK_STAR;
	}
	else {
		board[to_x][to_y] = BLK_BALL;
	}
	board[from_x][from_y] = BLK_PLAYER;
	board[px][py] = BLK_FLOOR;

	px = from_x;
	py = from_y;

	// add penalty (+1)

	return true;
}

// simply move player to the given position
void AStarState::movePlayer(int nx, int ny) {
	if(board[nx][ny] != BLK_FLOOR) {
		cerr << "Error: player stuck in an strange place" << endl;
		exit(-1);
	}
	board[px][py] = BLK_FLOOR;
	board[nx][ny] = BLK_PLAYER;

	px = nx;
	py = ny;
}

// browse whole board and find if there's a box
bool AStarState::isEnd() {
	for(auto &row : board) {
		for(auto &c : row) {
			if(c == BLK_BOX) return false;
		}
	}
	return true;
}