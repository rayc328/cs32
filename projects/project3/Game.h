#ifndef GAME_H
#define GAME_H

#include <iostream>
using namespace std;

#include "Board.h"
#include "Side.h"

class Player;

class Game
{
private:
	Board m_board; 
	Player* northPlayer; //use of pointers to player so we can utilize polymorphism due to there being derived players 
	Player* southPlayer; 
	Side m_turn; 
		
public: 
	Game(const Board& b, Player* south, Player* north);
	void display() const;
	void status(bool& over, bool& hasWinner, Side& winner) const;
	bool move(Side s);
	void play();
	int beans(Side s, int hole) const;
};

#endif
