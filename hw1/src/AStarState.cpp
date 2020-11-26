#include "AStarState.h"
#include <iostream>
#include <string>

using namespace std;

// bool State::operator==(const State* const& s) const {
// 	return (*this)->key == s->key;
// }

// load to board vector + encode to state key
// for init_state ONLY
AStarState::AStarState(int n, int m, BoardData data) {
	this->n = n;
	this->m = m;
	this->loadBoard(data); // also set px, py
	this->key = encode();
	this->penalty = 0; // init state penalty = 0
	// this->moves is a STL stack
	// printBoard();
}


// load data to the vector, locate player position
void AStarState::loadBoard(BoardData data) {
	// this->data = data;

	this->board.resize(n);
	for(auto i=0; i<n; i++) {
		this->board[i].resize(m);
		for(auto j=0; j<m; j++) {
			if(data.at(i*m + j) == BLK_PLAYER) {
				px = i;
				py = j;
			}
			this->board[i][j] = data.at(i*m + j);
		}
	}
}

void AStarState::printBoard() {
	for(auto &row : this->board) {
		for(auto &c : row) cout << c;
		cout << endl;
	}
	// usleep(200000); // delay 0.2s
}

void AStarState::setState(State s) {
	this->key = s.key;
	this->moves = s.moves;
	this->penalty = s.penalty;
	this->decode(); // AStarState attributes: load board, set px, py
}

State AStarState::getState() {
	State s;
	s.key = this->key;
	s.penalty = this->penalty;
	s.moves = this->moves;
	return s;
}

void AStarState::printMoves() {
	cout << penalty << endl;
	for(auto &d : moves) {
		switch(d) {
			case MOV_UP:
			case PUSH_UP:
				cout << "^";
				break;
			case MOV_DOWN:
			case PUSH_DOWN:
				cout << "v";
				break;
			case MOV_LEFT:
			case PUSH_LEFT:
				cout << "<";
				break;
			case MOV_RIGHT:
			case PUSH_RIGHT:
				cout << ">";
				break;
			default:
				break;	
		}
	}
	cout << endl;
}


// loadBoard() before usings
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
// autoload to board vector from the state key
void AStarState::decode() {
	loadBoard(key);
}

unsigned int AStarState::heuristic() {
	return 0;
}

unsigned int AStarState::estimate() {
	return penalty + heuristic();
}

unsigned int AStarState::cost() {
	return penalty;
}

/*^^^^^^^^^^^^^^^^^^^^^^^^ state attributes ^^^^^^^^^^^^^^^^^^^^^^^*/
/*vvvvvvvvvvvvvvvvvvvvvvvvv gameplay rules vvvvvvvvvvvvvvvvvvvvvvvv*/

// update AStarState board vector after the move, return false if the move is invalid
bool AStarState::nextMove(Direction next) { // 1-byte unsigned char
	int next_px = px + dx(next);
	int next_py = py + dy(next);

	if(!isValid(next_px, next_py)) {
		return false;
	}

	// push items
	char next_blk = board[next_px][next_py];
	if((next_blk == BLK_BOX || next_blk == BLK_STAR)) {
		next ^= MOV_MASK;
		if(!pushBox(next_px, next_py)) {
			return false;
		}
	}
	else if(next_blk == BLK_BALL) {
		next ^= MOV_MASK;
		if(!slideBall(next_px, next_py)) {
			return false;
		}
	}
	// move player
	else {
		movePlayer(next_px, next_py);
	}

	// push direction to history moves
	this->moves.push_back(next);
	// cout << "depth: " << moves.size() << endl;

	// update the StateKey!!!
	this->key = encode();

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
		if(board[nx][ny] == BLK_BALL || board[nx][ny] == BLK_STAR) return false;
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
	if(starBox) penalty += 2;
	else penalty += 1;

	return true;
}

// slide balls
bool AStarState::slideBall(int from_x, int from_y) {
	// ball's moving direction
	int _dx = from_x - px;
	int _dy = from_y - py;

	int to_x = from_x + _dx;
	int to_y = from_y + _dy;
	
	if(!isValid(to_x, to_y, BLK_BALL)) return false;

	while(isValid(to_x+_dx, to_y+_dy, BLK_BALL) && board[to_x+_dx][to_y+_dy] == BLK_FLOOR) {
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
	penalty += 1;

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

	penalty += 1;
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