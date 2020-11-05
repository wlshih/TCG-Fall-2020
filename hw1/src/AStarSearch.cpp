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
	// clear stack and queue, release Nodes and Boards

	// release closed list objects
	for(State* s : closed_list) {
		delete s;
	}
}

void AStarSearch::search() {
	// push the Node of init_state to open list
	Node start;
	open_list.push(start);
	while(!open_list.empty()) {
		// pop smallest node x from the open list
		Node x = open_list.top();
		loadCurrentState(x);
		open_list.pop();

		// test if x is an ending state
		current_state->isEnd();

		// generate successors of x and add to open list
		// and insert state on the closed list
		genSuccessor();

		// close this state
		delete current_state;
	}

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
		current_state->nextMove(x.dir);
		// current_state->encode();
	}

}

// x -> y
void AStarSearch::genSuccessor() {
	State *s = new State();
	*s = current_state->getState();

	// generate new nodes
	// point new nodes' parent to the strings (StateKey) in the closed list
	for(auto d = MOV_UP; d <= MOV_LEFT; d = (d<<1)) {
		// 4 direction Nodes
		if(!current_state->moves.empty() && current_state->moves.back() == reverseDir(d)) continue;
		
		Node y(s, d);
		AStarState _state(*current_state);
		_state.nextMove(d);
		// search closed list to check if the successors have been visited
		if(closed_list.count(&_state)) continue;
		
		// decide to trim or not
		// trim();

		// add y to the open list
		open_list.push(y);

	}

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