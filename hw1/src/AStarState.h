#ifndef ASTARSTATE_H
#define ASTARSTATE_H

#include <string>
#include <vector>

// origin input data, not the one stored on closed list
typedef std::string BoardData;
// encoded data stored on closed list
typedef std::string StateKey;

// 4: previous move, 4: current move, 
// b'0001: up(^),
// b'0010: right(>), 
// b'0100: down(v), 
// b'1000: left(<), 
// b'0000: no move, 
// b'1111: [error]
typedef unsigned char Direction;

#define MOV_UP    (unsigned char)0b0001
#define MOV_RIGHT (unsigned char)0b0010
#define MOV_DOWN  (unsigned char)0b0100
#define MOV_LEFT  (unsigned char)0b1000
#define MOV_NONE  (unsigned char)0b0000
#define MOV_MASK  (unsigned char)0b1111

#define BLK_WALL   (char)35
#define BLK_PLAYER (char)64
#define BLK_BOX    (char)36
#define BLK_BALL   (char)79
#define BLK_STAR   (char)42
#define BLK_FLOOR  (char)45


class AStarState {
private:
	int n;       // rows
	int m;       // cols
	// BoardData data;  // may be unused
	StateKey key;
	std::vector<std::vector<char> > board;

	int px;  // player's position
	int py;
	Direction dir; // what lead to this state
	
public:
	AStarState() {}
	AStarState(StateKey);
	AStarState(int, int, BoardData);
	// ~AStarState();

	void loadBoard(BoardData);
	void printBoard();

	void decode(StateKey);
	StateKey encode(); 

	int heuristic();

	bool nextMove(Direction);
	int dx(Direction);
	int dy(Direction);
	bool isValid(int, int);
	bool isValid(int, int, char);
	bool pushBox(int, int);
	bool slideBall(int, int);
	void movePlayer(int, int);
	bool isEnd();
};



#endif