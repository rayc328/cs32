#include <iostream>
#include <string>
using namespace std;

#include "Game.h"
#include "Player.h"
#include "Side.h"

Game::Game(const Board& b, Player* south, Player* north) : m_board(b), southPlayer(south), northPlayer(north)
{
	m_turn = SOUTH; //South player starts first
}

void Game::display() const
{
	cout << '\n'; 
	int whiteSpacetoPrint = ((m_board.holes() - 2)*4) - 1; 

	////////////////////////////
	//printing out north player name
	////////////////////////////
	for (int i = 0; i < 9; i++)
	{
		cout << " "; 
	}
	cout << "North (" << northPlayer->name() << ")" << endl;

	////////////////////////////
	//printing out north's holes
	////////////////////////////
	for (int i = 1; i <= m_board.holes(); i++)  
	{
		cout << "(" << m_board.beans(NORTH, i) << ") "; 
	}
	cout << endl; 

	////////////////////////////
	//printing out row WITH POTS
	////////////////////////////
	cout << "[" << m_board.beans(NORTH, POT) << "]N"; //printing north's pot
	
	for (int i = 0; i < whiteSpacetoPrint; i++)
	{
		cout << " "; 
	}

	cout << "S[" << m_board.beans(SOUTH, POT) << "]"; //printing south's pot 
	cout << endl; 
	
	////////////////////////////
	//printing out south's holes
	////////////////////////////
	for (int i = 1; i <= m_board.holes(); i++) //printing out south's holes 
	{
		cout << "(" << m_board.beans(SOUTH, i) << ") ";
	}
	cout << endl; 

	////////////////////////////
	//printing out south player name
	////////////////////////////
	for (int i = 0; i < 9; i++)
	{
		cout << " ";
	}
	cout << "South (" << southPlayer->name() << ")" << endl; 

}

void Game::status(bool& over, bool& hasWinner, Side& winner) const
{
	//if it is s's turn and s has no beans, then the game is over 
	if ( (m_board.beansInPlay(NORTH) == 0 && m_turn == NORTH) || (m_board.beansInPlay(SOUTH) == 0 && m_turn == SOUTH) )
	{
		over = true;

		int totalNorthBeans = m_board.beansInPlay(NORTH) + m_board.beans(NORTH, POT);
		int totalSouthBeans = m_board.beansInPlay(SOUTH) + m_board.beans(SOUTH, POT); 

		if (totalNorthBeans > totalSouthBeans) //NORTH WINS
		{
			hasWinner = true; 
			winner = NORTH; 
		}
		else if (totalSouthBeans > totalNorthBeans) //SOUTH WINS
		{
			hasWinner = true;
			winner = SOUTH;
		}
		else //game results in a tie 
		{
			hasWinner = false; 
		}
	}
	else
		over = false; 
}

bool Game::move(Side s) 
{
	Side endSide;
	int endHole;
	int holeToSow;

	if (m_board.beansInPlay(s) == 0) //side s has no holes with beans to pick up and sow, sweep any beans in s's opponent's holes into that opponent's pot and return false.
	{
		if (s == NORTH)
		{
			cout << "Sweeping remainder of SOUTH's beans into the pot of SOUTH" << endl;
		}
		else
		{
			cout << "Sweeping remainder of NORTH's beans into the pot of NORTH" << endl; 
		}

		Side opp = opponent(s);
		for (int i = 1; i <= m_board.holes(); i++)
		{
			m_board.moveToPot(opp, i, opp);
		} 
		return false; 
	}

	else if (s == SOUTH)
	{
		holeToSow = southPlayer->chooseMove(m_board, SOUTH); //get the move 

		if (southPlayer->isInteractive() == false)
		{
			cout << southPlayer->name() << " (SOUTH) chooses hole " << to_string(holeToSow) << endl; 
		}

		m_board.sow(SOUTH, holeToSow, endSide, endHole); 

		if (endSide == SOUTH && endHole == POT) //If the last bean was placed in the player's pot, the player must take another turn.
		{
			display(); //display board when the player gets additional turn
			cout << southPlayer->name() << "(SOUTH) gets an additional turn!" << endl;
			return move(SOUTH); //recursive call 
		}
		else if (endSide == SOUTH && m_board.beans(SOUTH, endHole) - 1 == 0 && m_board.beans(NORTH,endHole) != 0) //capture 
		{
			cout << southPlayer->name() << "(SOUTH) made a capture!" << endl;
			m_board.moveToPot(NORTH, endHole, SOUTH); //all beans in the opponent's hole directly opposite from that hole are put into the player's pot
			m_board.moveToPot(SOUTH, endHole, SOUTH); //last bean moved into player's pot 
		}

		m_turn = NORTH; //change turns after 
	}

	else if (s == NORTH)
	{
		holeToSow = northPlayer->chooseMove(m_board, NORTH);

		if (northPlayer->isInteractive() == false)
		{
			cout << northPlayer->name() << " (NORTH) chooses hole " << to_string(holeToSow) << endl;
		}

		m_board.sow(NORTH, holeToSow, endSide, endHole); //make move, initializes endSide and endhole

		if (endSide == NORTH && endHole == POT) //If the last bean was placed in the player's pot, the player must take another turn.
		{
			display(); //display board when the player gets additional turn
			cout << northPlayer->name() << "(NORTH) gets an additional turn!" << endl;
			return move(NORTH); //recursive call  
		}
		else if (endSide == NORTH && m_board.beans(NORTH, endHole) - 1 == 0 && m_board.beans(SOUTH, endHole) != 0) //capture 
		{
			cout << northPlayer->name() << "(NORTH) made a capture!" << endl; 
			m_board.moveToPot(SOUTH, endHole, NORTH); //all beans in the opponent's hole directly opposite from that hole are put into the player's pot
			m_board.moveToPot(NORTH, endHole, NORTH); //last bean moved into player's pot 
		}

		m_turn = SOUTH; //change turns after 
	}

	return true; 
}

void Game::play()
{
	bool isOver;
	bool hasWinner;
	Side winner;

	status(isOver, hasWinner, winner);
	display(); 

	while (isOver == false)
	{
		move(m_turn); //turn is being updated everytime move is called 
		display(); 
		//if (northPlayer->isInteractive() == false && southPlayer->isInteractive() == false)  //neither play is interactive, ie both are bots
		//{
		//	cout << '\n'; 
		//	cout << "Hit ENTER to proceed.";
		//	cin.ignore(1000, '\n');
		//}
		status(isOver, hasWinner, winner); //update the status of game 
	}

	move(m_turn);
	display(); 
	if (hasWinner == true)
	{
		if (winner == NORTH)
			cout << northPlayer->name() << " (NORTH) wins!" << endl;

		else if (winner == SOUTH)
			cout << southPlayer->name() << " (SOUTH) wins!" << endl; 
	}
	else
	{
		cout << "The game ended in a tie." << endl; 
	}
}

int Game::beans(Side s, int hole) const
{
	if (hole < 0 || hole > m_board.holes())
	{
		return -1; 
	}

	return m_board.beans(s, hole); 
}