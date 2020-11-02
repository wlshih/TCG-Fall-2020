#ifndef ASTARSTATE_H
#define ASTARSTATE_H

#include <string>
#include <vector>

typedef std::string Board;

class AStarState {
private:
	int n;  // rows
	int m;  // cols
	std::vector<std::vector<char>> map;
	Board state;
	
public:
	AStarState();
	AStarState(int, int, std::string);
	// ~AStarState();
	void decode(Board);
	Board encode();
	int heuristic();
	bool testGoal();

	void printBoard();
};



#endif