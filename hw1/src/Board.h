#ifndef BOARD_H
#define BOARD_H

#include <string>

typedef std::string State;

class Board {
private:
	int n;
	int m;

	
public:
	Board();
	~Board();
	void decode(State);
	State encode();
	
};



#endif