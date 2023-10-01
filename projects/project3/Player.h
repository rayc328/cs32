#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>

#include "Side.h"
using namespace std;

class Board;

class Player
{
private:
	std::string m_PlayerName;

public:
	Player(std::string name);
	std::string name() const;
	virtual bool isInteractive() const;
	virtual int chooseMove(const Board& b, Side s) const = 0;
	virtual ~Player();
};

///////////////////
///HUMAN PLAYER
//////////////////
class HumanPlayer : public Player
{
public:
	HumanPlayer(string name);
	virtual bool isInteractive() const; //returns true 
	virtual int chooseMove(const Board& b, Side s) const;
	virtual ~HumanPlayer(); 
};


///////////////////
///BAD PLAYER
//////////////////
class BadPlayer : public Player
{
public:
	BadPlayer(string name); 
	virtual int chooseMove(const Board& b, Side s) const;
	virtual ~BadPlayer();
};

class SmartPlayer : public Player
{
public:
	SmartPlayer(string name);
	virtual int chooseMove(const Board& b, Side s) const;
	virtual ~SmartPlayer();
private:
	int eval(const Board& b) const;
	void makeSmartMove(const Board& b, Side s, int depth, int& bestHole, int& heuristic) const;
	bool sowANDcapture(Board& b, Side s, int hole, Side& endSide, int& endHole) const;
};

#endif


