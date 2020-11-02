#include "AStarSearch.h"
#include <string>
#include <iostream>

using namespace std;

AStarSearch::AStarSearch(int n, int m, string board) {
	this->init_state = new AStarState(n, m, board);
	this->move_stack.push(this->init_state);
}

AStarSearch::~AStarSearch() {
	delete this->init_state;
	// clear stack and queue, release Nodes and Boards
}

void AStarSearch::search() {
	// push the Node of init_state to open list
	// open_list.push()

}