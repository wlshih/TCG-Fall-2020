#ifndef ASTARSEARCH_H
#define ASTARSEARCH_H

#include <vector>
#include <queue>
#include <stack>
#include "Board.h"

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
	std::priority_queue<Node> open_list;
	// hash closed_list;
	// int depth; // for IDA

public:
	AStarSearch();
	~AStarSearch();
	int heuristic();

};

// size: 8+12+12=32 bits
struct Node {
	Direction dir;
	unsigned int depth : 12; // how many moves
	unsigned int cost  : 12; // current cost + heuristic
};


#endif