#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
using namespace std;

#include "Side.h" 

class Board
{
private: 
	int m_holes; //number of holes on each side 
	int m_beans; //number of beans per hole 
	
	vector<int> northHoles; 
	vector<int> southHoles; 
	
public: 
	Board(int nHoles, int nInitialBeansPerHole);
	int holes() const;
	int beans(Side s, int hole) const;
	int beansInPlay(Side s) const;
	int totalBeans() const;
	bool sow(Side s, int hole, Side& endSide, int& endHole);
	bool moveToPot(Side s, int hole, Side potOwner);
	bool setBeans(Side s, int hole, int beans);
};

#endif