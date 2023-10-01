#include <iostream>
#include <vector>
using namespace std;

#include "Board.h"

Board::Board(int nHoles, int nInitialBeansPerHole)
{
	if (nHoles <= 0) //nHoles not positive 
		m_holes = 1;
	else
		m_holes = nHoles;

	if (nInitialBeansPerHole < 0)
		m_beans = 0;
	else
		m_beans = nInitialBeansPerHole;

	northHoles.resize(1 + m_holes); //initialize NORTH holes (add 1 to account for the pot) 
	southHoles.resize(1 + m_holes); //initialize SOUTH holes
	
	//set pots to be 0
	northHoles[POT] = 0; 
	southHoles[POT] = 0; 

	for (int i = 1; i <= m_holes; i++)
	{
		northHoles[i] = m_beans; //fill each hole with particular number of beans
		southHoles[i] = m_beans; 
	}
}

int Board::holes() const //return number of holes on a side (not counting the pot) 
{
	return m_holes;
}

int Board::beans(Side s, int hole) const //Return the number of beans in the indicated hole or pot, or -1 if the hole number is invalid.
{
	if (hole < 0 || hole > m_holes)//invalid hole or pot
	{
		return -1;
	}
	
	if (s == NORTH)
		return northHoles[hole]; 

	return southHoles[hole]; 
}

int Board::beansInPlay(Side s) const //return total number of beans in all holes on the indicated side (excluding pot)
{
	int totalBeans = 0;

	if (s == NORTH)
	{
		for (int i = 1; i <= m_holes; i++)
		{
			totalBeans += northHoles[i];
		}

		return totalBeans; 
	}
	else
	{
		for (int i = 1; i <= m_holes; i++)
		{
			totalBeans += southHoles[i];
		}

		return totalBeans;
	}
}

int Board::totalBeans() const //total number of beans in the game 
{
	return beansInPlay(NORTH) + beansInPlay(SOUTH) + northHoles[POT] + southHoles[POT];
}
 
bool Board::sow(Side s, int hole, Side& endSide, int& endHole)
{
	if (hole <= POT || hole > m_holes) //hole is pot or invalid
		return false;

	int beansToSow = 0;

	if (s == NORTH && northHoles[hole] == 0) //checking for empty hole
	{
		return false;
	}
	else if (s == SOUTH && southHoles[hole] == 0) //checking for empty hole
	{
		return false; 
	}
	else
	{
		if (s == SOUTH)
		{
			beansToSow = southHoles[hole];
			southHoles[hole] = 0; //emptying the selected hole
		}

		else if (s == NORTH)
		{
			beansToSow = northHoles[hole];
			northHoles[hole] = 0; //emptying the selected hole
		}
	}

	Side currentSide = s; 
	int currentHole = hole; 

	while (beansToSow > 0)
	{
		if (currentSide == NORTH && currentHole == 1)
		{
			if (opponent(s) == NORTH) //skip opponent North's pot
			{
				currentSide = SOUTH; 
				currentHole = 1;  
				southHoles[currentHole]++; 
				beansToSow--; 
				continue;
			}
			else
			{
				currentHole = POT;
				northHoles[POT]++;
				beansToSow--;
				continue;
			}
		}

		if (currentSide == NORTH && currentHole == POT)
		{
			currentSide = SOUTH;
			currentHole = 1; 
			southHoles[currentHole]++; 
			beansToSow--; 
			continue;
		}

		if (currentSide == SOUTH && currentHole == m_holes)
		{
			if (opponent(s) == SOUTH) //skip opponent South's pot
			{
				currentSide = NORTH;
				northHoles[currentHole]++;
				beansToSow--;
				continue;
			}
			else 
			{
				currentHole = POT;
				southHoles[currentHole]++;
				beansToSow--;
				continue;
			}
		}

		if (currentSide == SOUTH && currentHole == POT)
		{
			currentSide = NORTH;
			currentHole = m_holes; 
			northHoles[currentHole]++; 
			beansToSow--;
			continue;
		}

		if (currentSide == NORTH && currentHole > 1 && currentHole <= m_holes) //if this statement gets run, then the hole should be in the range 1 < x <= m_holes
		{
			currentHole--; //counterclockwise nature, eg. if we are at hole 6 of north and still have beans remaining, we want to drop a bean in hole 5
			northHoles[currentHole]++; 
			beansToSow--; 
			continue;
		}

		if (currentSide == SOUTH && currentHole >= 1 && currentHole < m_holes) //if this statement gets run, then the hole should be in the range 1 <= x < m_holes
		{
			currentHole++;
			southHoles[currentHole]++; 
			beansToSow--; 
			continue;
		}
	}

	endSide = currentSide; 
	endHole = currentHole; 

	return true; 
}

bool Board::moveToPot(Side s, int hole, Side potOwner) //do we check if the hole is empty? 
{
	if (hole <= POT || hole > m_holes || beans(s,hole) == 0) //checking for invalid hole, no beans in the selected hole 
		return false; 

	if (s == NORTH && potOwner == SOUTH)
	{
		southHoles[POT] += northHoles[hole];
		northHoles[hole] = 0; //empty particular hole
		return true; 
	}
	
	if (s == SOUTH && potOwner == NORTH)
	{
		northHoles[POT] += southHoles[hole];
		southHoles[hole] = 0; //empty particular hole
		return true; 
	}

	if (s == SOUTH && potOwner == SOUTH)
	{
		southHoles[POT] += southHoles[hole];
		southHoles[hole] = 0;
		return true;
	}

	if (s == NORTH && potOwner == NORTH)
	{
		northHoles[POT] += northHoles[hole];
		northHoles[hole] = 0;
		return true;
	}

	return false;
}

bool Board::setBeans(Side s, int hole, int beans) //for testing purposes
{
	if (hole < POT || hole > m_holes || beans < 0)
	{
		return false;
	}

	else if (s == NORTH)
	{
		northHoles[hole] = beans; 
		return true; 
	}
	else
	{
		southHoles[hole] = beans;
		return true; 
	}
}