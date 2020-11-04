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
	delete this->current_state;
	// clear stack and queue, release Nodes and Boards
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

		// push current stateKey on the closed list before genSuccessor()
		// because the successors need to reference the closed list
		closed_list.insert(current_state->encode());

		// generate successors of x and add to open list
		genSuccessor();

		// close this state
		delete current_state;
	}

}

// load to attribute [and return a StateKey]
void AStarSearch::loadCurrentState(Node x) {
	// root node, current state is the initial state
	if(x.prevState == NULL) {
		current_state = new AStarState(*init_state);
		// cout << current_state->encode() << endl;
	}
	else {
		current_state = new AStarState(*x.prevState);
		current_state->nextMove(x.dir);
		// current_state->encode();
	}

	// return current_state->encode();
}

// x -> y
void AStarSearch::genSuccessor() {
	// generate new nodes
	// point new nodes' parent to the strings (StateKey) in the closed list
	for(auto d = MOV_UP; d <= MOV_LEFT; d = (d<<1)) {
		Node y((current_state->dir << 4) | d);

		// y.parent = closed_list.find(current_state->encode());
		// cout << (int)y.dir << endl;
	}
	// search closed list to check if the successors have been visited
	// add to open list

}