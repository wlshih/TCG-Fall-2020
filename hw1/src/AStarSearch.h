#ifndef ASTARSEARCH_H
#define ASTARSEARCH_H

#include <queue>
#include <unordered_set>
#include "AStarState.h"


// size: 32+8+12+12=64 bits
struct Node {
	State* prevState;        // 4-byte pointer
	Direction dir;           // 1-byte unsigned char
	unsigned int cost : 12;  // how many moves (with penalty)
	unsigned int est  : 12;  // current cost + heuristic

	Node() : prevState(NULL), dir(MOV_NONE), cost(0), est(0) {}
	Node(State* s, Direction D, unsigned int c, unsigned int e) : prevState(s), dir(D), cost(c), est(e) {}
	// Node(Direction D, unsigned int c) : dir(D), cost(c) {}
	// Node(Direction D, unsigned int d, unsigned int c) : dir(D), depth(d), cost(c) {}
};

struct CompareNode {
	bool operator()(const Node& n1, const Node& n2) {
		return (n1.est > n2.est);
	}
};

struct PointedStateHash {
	bool operator()(State* const& s) const {
		return std::hash<std::string>()(s->key);
	}
};

struct PointedStateEq {
	bool operator()(State const* s1, State const* s2) const {
		return s1->key == s2->key;
	}
};

class AStarSearch {
private:
	AStarState *init_state;     // the origin stage map
	AStarState *current_state;  // current expanding state
	// std::stack<AStarState*> move_history;

	std::priority_queue<Node, std::vector<Node>, CompareNode> open_list;
	std::unordered_set<State*, PointedStateHash, PointedStateEq> closed_list;
	// int threshold; // for IDA*

public:
	AStarSearch();
	AStarSearch(int, int, BoardData);
	~AStarSearch();
	bool search();
	void loadCurrentState(Node);
	void genSuccessor();
	Direction reverseDir(Direction);
	void printPlay();

};



#endif