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
	// clear stack and queue, release Nodes and Boards
}

void AStarSearch::search() {
	// push the Node of init_state to open list
	Node start;
	open_list.push(start);

	while(!open_list.empty()) {
		// pop smallest node x from the open list
		Node x = open_list.top();
		open_list.pop();
		loadCurrentState(x);

		// test if x is an ending state
		current_state->isEnd();

		// generate successors of x and add to open list
		genSuccessor();

		// push x on the closed list
		// closed_list.insert(current_state->encode());

		// auto lookup = closed_list.find(current_state->encode());
		// cout << *lookup << endl;
	}

}

void AStarSearch::loadCurrentState(Node x) {
	// root node, current state is the initial state
	if(x.parent == NULL) {
		current_state = new AStarState(*init_state);
		// cout << current_state->encode() << endl;
	}
	else {
		current_state = new AStarState();
		// current_state->loadBoard(x.parent->decode());
	}

}

void AStarSearch::genSuccessor() {
	// generate new nodes
	// point new nodes' parent to the strings (State) in the closed list
	for(auto i=0; i<4; i++) {
		Node y(MOV_UP << i);
		// y.parent = closed_list.find(current_state->encode());
		// cout << (int)y.dir << endl;
	}
	// search closed list to check if the successors have been visited
	// add to open list

}