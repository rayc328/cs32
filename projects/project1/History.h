#ifndef HISTORY_H
#define HISTORY_H

#include <iostream>
#include "globals.h"

using namespace std; 

class History
{
public:
	History(int nRows, int nCols);
	bool record(int r, int c);
	void display() const;

private: 
	int mRows; 
	int mColumns; 
	int mGrid[MAXROWS][MAXCOLS];
};

#endif 