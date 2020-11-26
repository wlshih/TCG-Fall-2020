#include "AStarSearch.h"
#include <string>
#include <iostream>

using namespace std;

AStarSearch::AStarSearch(int n, int m, BoardData data) {
	this->init_state = new AStarState(n, m, data);
	// this->move_history.push(this->init_state);
}

AStarSearch::~AStarSearch() {
	delete this->init_state;
	// delete this->current_state;

	// release closed list objects
	for(State* s : closed_list) {
		delete s;
	}
}

bool AStarSearch::search() {
	// push the Node of init_state to open list
	Node start;
	open_list.push(start);
	while(!open_list.empty()) {
		// pop smallest node x from the open list
		Node x = open_list.top();
		loadCurrentState(x); // new object
		open_list.pop();

		// current_state->printBoard();

		// test if x is an ending state
		if(current_state->isEnd()) {
			// cout << "[Moves]: ";
			current_state->printMoves();
			// printPlay();

			return true;
		}
		// generate successors of x and add to open list
		// and insert state on the closed list
		// cout << open_list.size() << " > ";
		genSuccessor();
		// cout << " > " << open_list.size() << endl;

		// close this state
		delete current_state;
	}

	return false;

}

// create a current_state and load to attribute
void AStarSearch::loadCurrentState(Node x) {
	// root node, current state is the initial state
	if(x.prevState == NULL) {
		current_state = new AStarState(*init_state);
		// cout << current_state->encode() << endl;
	}
	// non-root, load from x.prevState
	else {
		current_state = new AStarState(*init_state);
		current_state->setState(*x.prevState);
		// current_state->printBoard();
		if(!current_state->nextMove(x.dir)) {
			cerr << "Why you walk again??" << endl;
			exit(-1);
		}
		// current_state->printBoard();
		// current_state->encode();
	}

}

// x -> y
void AStarSearch::genSuccessor() {
	// s is for closed list
	State *s = new State();
	*s = current_state->getState();
	// cout << string(20, '.') << endl;
	// current_state->printBoard();
	// cout << endl;

	// generate new nodes
	// point new nodes' parent to the strings (StateKey) in the closed list
	for(auto d = MOV_UP; d <= MOV_LEFT; d = (d<<1)) {
		// 4 direction Nodes
		if(!s->moves.empty() && s->moves.back() == reverseDir(d)) {
			// cout << "[BACK]";
			continue;
		}
		AStarState _state(*current_state);
		if(!_state.nextMove(d)) {
			// cout << "[INVALID]";
			continue;
		}
		// else _state.printBoard();

		// _state.printMoves();
		// search closed list to check if the successors have been visited
		if(closed_list.count(&_state)) {
			// cout << "[REPETED]";
			continue;
		}
		
		// trim();

		// y is for open list
		Node y(s, d, _state.cost(), _state.estimate());
		// add y to the open list
		open_list.push(y);
		// cout << "[*]";
		// _state.printBoard();
		// cout << endl;

	}
	// add s(derived from x) to the closed list
	closed_list.insert(s);

}

Direction AStarSearch::reverseDir(Direction D) {
	D &= MOV_MASK;
	switch(D) {
		case MOV_UP:
			return MOV_DOWN;
		case MOV_DOWN:
			return MOV_UP;
		case MOV_RIGHT:
			return MOV_LEFT;
		case MOV_LEFT:
			return MOV_RIGHT;
		default:
			cerr << "Error: why walking this way?" << endl;
			exit(1);
	}
}


// debug
void AStarSearch::printPlay() {
	AStarState play(*init_state);
	play.printBoard();
	cout << endl;
	for(auto &d : current_state->moves) {
		play.nextMove(d);
		play.printBoard();
		cout << endl;
	}
}