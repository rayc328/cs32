#include "History.h"
#include "Rabbit.h"
#include "Arena.h"
#include "globals.h"

History::History(int nRows, int nCols) : mRows(nRows), mColumns(nCols)
{
	//assuming History object that it will be called with a first argument 
	//that does not exceed MAXROWS and a second that does not exceed MAXCOLS, 
	//and that neither argument will be less than 1

	for (int i = 0; i < mRows; i++) //initializing the 2D array that represents a GRID 
	{
		for (int j = 0; j < mColumns; j++)
			mGrid[i][j] = 0; //each plot of the grid starts at 0, everytime a poison rabbit gets on it we increment by 1
	}
}

bool History::record(int r, int c)
{
	if (r >= 1 && r <= mRows && c >= 1 && c <= mColumns)
	{
		mGrid[r - 1][c - 1]++; //counter of how many poisoned rabbits had been on that specific grid point 
		return true;
	}
	else
	{
		return false;
	}
}

void History::display() const
{
	clearScreen();
	for (int rowIndex = 0; rowIndex < mRows; rowIndex++)
	{
		for (int colIndex = 0; colIndex < mColumns; colIndex++)
		{
			if (mGrid[rowIndex][colIndex] == 0)
			{
				cout << "."; 
			}
			else if (mGrid[rowIndex][colIndex] <= 25 && mGrid[rowIndex][colIndex] > 0)
			{
				cout << char('A' + (mGrid[rowIndex][colIndex] - 1)); //ascii value (1 poisonous rabbits is A, 2 poisonous rabbits is B) 
			}
			else 
			{
				cout << 'Z'; 
			}; 
		}
		cout << endl;
	}
	cout << endl;
	
	//write an empty line after the history grid 
}