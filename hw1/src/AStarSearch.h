#ifndef ASTARSEARCH_H
#define ASTARSEARCH_H

#include <vector>
#include <queue>
#include <stack>
#include "AStarState.h"

// 4: previous move, 4: current move, 
// b'0001: up(^),
// b'0010: right(>), 
// b'0100: down(v), 
// b'1000: left(<), 
// b'0000: no move, 
// b'1111: [error]
typedef unsigned char Direction;

struct Node;

class AStarSearch {
private:
	AStarState* init_state;
	AStarState* current_state;
	std::stack<AStarState*> move_stack;
	std::priority_queue<Node*> open_list;
	// std::unordered_set<State> closed_list;
	// int depth; // for IDA

public:
	AStarSearch();
	AStarSearch(int, int, std::string);
	~AStarSearch();
	void search();

};

// size: 8+12+12=32 bits
struct Node {
	Direction dir;            // unsigned char
	unsigned int depth : 12;  // how many moves
	unsigned int cost  : 12;  // current cost + heuristic

	Node() : dir(0), depth(0), cost(0) {}
	Node(Direction D, unsigned int d, unsigned int c) : dir((dir<<4) + D), depth(d), cost(c) {}
};


#endif