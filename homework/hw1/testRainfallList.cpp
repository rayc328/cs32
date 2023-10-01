#include <iostream>
using namespace std; 
#include <cassert>
#include "RainfallList.h"

int main()
{
	RainfallList s; 
	assert(s.add(400) == true);
	assert(s.add(200) == true);
	assert(s.add(300) == true);
	assert(s.add(13) == true);
	assert(s.add(20) == true);
	assert(s.remove(2) == false);
	assert(s.size() == 5);
	assert(s.minimum() == 13);
	assert(s.maximum() == 400);
	assert(s.remove(400) == true);
	assert(s.remove(400) == false);
	cerr << "passed all cases!" << endl;
}
