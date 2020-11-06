#ifndef TYPES_H
#define TYPES_H

#include <string>
#include <vector>
#include <unistd.h>

// encoded data stored on closed list State
typedef std::string StateKey;
// origin input data, not the one stored on closed list
typedef std::string BoardData;


// 4: previous move, 4: current move, 
// b'0001: up(^),
// b'0010: right(>), 
// b'0100: down(v), 
// b'1000: left(<), 
// b'0000: no move, 
// b'1111: [error]
typedef unsigned char Direction;

#define MOV_UP     (unsigned char)0b0001
#define MOV_RIGHT  (unsigned char)0b0010
#define MOV_DOWN   (unsigned char)0b0100
#define MOV_LEFT   (unsigned char)0b1000
#define MOV_NONE   (unsigned char)0b0000
#define MOV_MASK   (unsigned char)0b1111
#define PUSH_UP    (unsigned char)0b1110
#define PUSH_RIGHT (unsigned char)0b1101
#define PUSH_LEFT  (unsigned char)0b1011
#define PUSH_DOWN  (unsigned char)0b0111

#define BLK_WALL   (char)35
#define BLK_PLAYER (char)64
#define BLK_BOX    (char)36
#define BLK_BALL   (char)79
#define BLK_STAR   (char)42
#define BLK_FLOOR  (char)45



#endif