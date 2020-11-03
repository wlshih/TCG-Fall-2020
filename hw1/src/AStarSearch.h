#ifndef ASTARSEARCH_H
#define ASTARSEARCH_H

#include <vector>
#include <queue>
#include <unordered_set>
#include "AStarState.h"

// 4: previous move, 4: current move, 
// b'0001: up(^),
// b'0010: right(>), 
// b'0100: down(v), 
// b'1000: left(<), 
// b'0000: no move, 
// b'1111: [error]
typedef unsigned char Direction;

#define MOV_UP    0b0001
#define MOV_RIGHT 0b0010
#define MOV_DOWN  0b0100
#define MOV_LEFT  0b1000
#define NONE  0b0000


// size: 8+12+12=32 bits
struct Node {
	AStarState* parent;       // 4-byte pointer
	Direction dir;            // 1-byte unsigned char
	unsigned int depth : 12;  // how many moves
	unsigned int cost  : 12;  // current cost + heuristic

	Node() {}
	Node(Direction D) : dir(D) {}
	Node(Direction D, unsigned int c) : dir(D), cost(c) {}
	Node(Direction D, unsigned int d, unsigned int c) : dir(D), depth(d), cost(c) {}
};

struct CompareNode {
	bool operator()(const Node& n1, const Node& n2) {
		return (n1.cost > n2.cost);
	}
};

class AStarSearch {
private:
	AStarState *init_state;     // the origin stage map
	AStarState *current_state;  // current expanding state
	// std::stack<AStarState*> move_history;

	std::priority_queue<Node, std::vector<Node>, CompareNode> open_list;
	std::unordered_set<std::string*> closed_list;
	// int threshold; // for IDA*

public:
	AStarSearch();
	AStarSearch(int, int, BoardData);
	~AStarSearch();
	void search();
	void loadCurrentState(Node);
	void genSuccessor();

};



#endif