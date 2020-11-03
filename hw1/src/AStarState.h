#ifndef ASTARSTATE_H
#define ASTARSTATE_H

#include <string>
#include <vector>

// origin input data, not the one stored on closed list
typedef std::string BoardData;
// encoded data stored on closed list
typedef std::string State;

class AStarState {
private:
	int n;       // rows
	int m;       // cols
	BoardData data;  // may be unused
	std::vector<std::vector<char> > board;
	
public:
	AStarState() {}
	AStarState(int, int, BoardData);
	// ~AStarState();

	void loadBoard(BoardData);
	void printBoard();

	void decode(State);
	State encode(); 

	int heuristic();
	bool isEnd();
};



#endif