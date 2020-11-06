#ifndef ASTARSTATE_H
#define ASTARSTATE_H

#include "types.h"

class State {
public:
	StateKey key;
	std::vector<Direction> moves;
	unsigned int penalty;
public:
	State() {}
	// bool operator==(const State&) const;
};

class AStarState : public State {
private:
	int n;       // rows
	int m;       // cols
	// BoardData data;  // may be unused
	// State state;
	std::vector<std::vector<char> > board;

	int px;  // player's position
	int py;
	// Direction dir; // current direction, what lead to this state
	
public:
	AStarState() {}
	// AStarState(StateKey);
	AStarState(int, int, BoardData);
	// ~AStarState();

	void loadBoard(BoardData);
	void printBoard();
	void setState(State);
	State getState();
	void printMoves();

	void decode();
	StateKey encode(); 

	int heuristic();
	int cost();

	bool isEnd();
	bool nextMove(Direction);
	int dx(Direction);
	int dy(Direction);
	bool isValid(int, int);
	bool isValid(int, int, char);
	bool pushBox(int, int);
	bool slideBall(int, int);
	void movePlayer(int, int);
};



#endif