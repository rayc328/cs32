#include <iostream>
#include <climits>
using namespace std; 

//header files 
#include "Side.h"
#include "Player.h"
#include "Board.h"

/////////////////////////////////
//////////////// ABSTRACT PLAYER (BASE CLASS)
/////////////////////////////////

Player::Player(std::string name)
{
	m_PlayerName = name; 
}

std::string Player::name() const 
{
	return m_PlayerName; 
}

bool Player::isInteractive() const //VIRTUAL //only return TRUE FOR HUMANPLAYER CLASS //default should return false 
{
	return false;
}

Player::~Player() //virtual destructor
{}


/////////////////////////////////
//////////////// HUMAN PLAYER (DERIVED CLASS) 
/////////////////////////////////

HumanPlayer::HumanPlayer(string name) : Player(name)
{}

HumanPlayer::~HumanPlayer()
{}

bool HumanPlayer::isInteractive() const
{
	return true;
}

int HumanPlayer::chooseMove(const Board& b, Side s) const //return -1 if no move is possible 
{
	if (b.beansInPlay(s) == 0) //no move is possible if player has no beans on their side 
	{
		return -1; 
	}

	bool validMove = false; 
	int holeNumber;

	do 
	{
		cout << "Enter a hole number: ";
		cin >> holeNumber;

		if (holeNumber < 1 || holeNumber > b.holes()) //if the hole is invalid
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Hole number is out of range." << endl; 
		}
		else if (b.beans(s, holeNumber) == 0) //hole number is valid but we need to check if the hole is empty
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Hole number is empty." << endl; 
		}
		else //if the upper two if statements are not entered then the holeNumber is valid and thus we stop the loop 
		{
			validMove = true;
		}

	} while (validMove == false);

	return holeNumber; 
}

/////////////////////////////////
//////////////// BAD PLAYER (DERIVED CLASS) 
/////////////////////////////////

BadPlayer::BadPlayer(string name) : Player(name)
{}

BadPlayer:: ~BadPlayer()//virtual destructor
{}

int BadPlayer::chooseMove(const Board& b, Side s) const 
{
	if (b.beansInPlay(s) == 0) //no move is possible if player has no beans on their side 
	{
		return -1;
	}
	
	for (int i = 1; i <= b.holes(); i++)
	{
		if (b.beans(s, i) > 0) //choose the leftmost hole that has beans in it 
		{
			return i; 
		}
	}
	return -1; 
}

/////////////////////////////////
//////////////// SMART PLAYER (DERIVED CLASS) 
/////////////////////////////////
SmartPlayer::SmartPlayer(string name) : Player(name)
{}

int SmartPlayer::chooseMove(const Board& b, Side s) const
{
	int depth = 5;
	int bestHole;
	int heuristic; 

	makeSmartMove(b, s, depth, bestHole, heuristic);
	return bestHole; 
}

int SmartPlayer::eval(const Board& b) const
{
	return b.beans(SOUTH, POT) - b.beans(NORTH, POT); //return difference between number of beans in SOUTH's pot vs NORTH's pot 
}

void SmartPlayer::makeSmartMove(const Board& b, Side s, int depth, int& bestHole, int& heuristic) const //helper function for choose move
{
	if (b.beansInPlay(s) == 0) //stopping conditions
	{
		bestHole = -1; 
		int diff = eval(b); 
		
		if (s == SOUTH)
		{
			if (diff > 0)
			{
				heuristic = INT_MAX; //south won, good for south
			}
			else if (diff < 0)
			{
				heuristic = INT_MIN; //north won, bad for south
			}
			else
				heuristic = 0; //tie
		}
		else if (s == NORTH)
		{
			if (diff > 0)
			{
				heuristic = INT_MIN; //south wins, bad for north
			}
			if (diff < 0)
			{
				heuristic = INT_MAX; //north wins, good for north
			}
			else
				heuristic = 0; //tie
		}
		return;
	}
	else if (depth <= 0) //stopping condition
	{
		bestHole = -1; 
		heuristic = eval(b); 
		return;
	}

	bestHole = -1; 
	if (s == SOUTH) //we want to maximize our heuristic value for SOUTH so we set a very low initial value
	{
		heuristic = INT_MIN; //min
	}
	else if (s == NORTH)
		heuristic = INT_MAX; //max
	//we want to minimize our heuristic value for NORTH so we set a very high initial value

	int firstPossibleHole = -1; //we store the first possible hole and later assign it so that smartplayer will never choose -1
	for (int i = 1; i <= b.holes(); i++) //if this for loop runs, there should always be AT least one available move 
	{
		if (b.beans(s, i) > 0)
		{
			firstPossibleHole = i;
			break;
		}
	}

	for (int i = 1; i <= b.holes(); i++)
	{
		if (b.beans(s, i) > 0) //ensures smart player is making a legal move 
		{
			Board boardCopy = b; //make a copy of the board that we can use to make moves
			Side endSide; 
			int endHole;

			int bestHole2;
			int h2; 
	
			sowANDcapture(boardCopy, s, i, endSide, endHole);

			if (endSide == s && endHole == POT) //additional move can be made 
			{
				bestHole = i;

				makeSmartMove(boardCopy, s, depth - 1, bestHole2, h2); //recursive call to make another move
				if ((s == SOUTH && h2 > heuristic) || (s == NORTH && h2 < heuristic))
				{ 
					heuristic = h2;
				}
			}
			else
			{
				makeSmartMove(boardCopy, opponent(s), depth - 1, bestHole2, h2); //recursive call on opponent
			}
			if (i == firstPossibleHole)
			{
				bestHole = i;
			}
			if ((s == SOUTH && h2 > heuristic) || (s == NORTH && h2 < heuristic))
			{
				bestHole = i; 
				heuristic = h2; 
			}
			
		}
	} 
}

bool SmartPlayer::sowANDcapture(Board& b, Side s, int hole, Side& endSide, int& endHole) const
{

	bool sowable = b.sow(s, hole, endSide, endHole);
	if (sowable == false)
	{
		return false;
	}

	if (s == SOUTH && endSide == SOUTH && b.beans(SOUTH, endHole) - 1 == 0 && b.beans(NORTH, endHole) != 0) //south makes capture 
	{
		b.moveToPot(NORTH, endHole, SOUTH); //all beans in the opponent's hole directly opposite from that hole are put into the player's pot
		b.moveToPot(SOUTH, endHole, SOUTH); //last bean moved into player's pot 
	}
	else if (s == NORTH && endSide == NORTH && b.beans(NORTH, endHole) - 1 == 0 && b.beans(SOUTH, endHole) != 0) //north makes capture 
	{
		b.moveToPot(SOUTH, endHole, NORTH); //all beans in the opponent's hole directly opposite from that hole are put into the player's pot
		b.moveToPot(NORTH, endHole, NORTH); //last bean moved into player's pot 
	}

	return true; 
}

SmartPlayer::~SmartPlayer() //virtual destructor 
{}