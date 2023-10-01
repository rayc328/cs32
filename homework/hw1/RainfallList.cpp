#include "RainfallList.h"
RainfallList::RainfallList() : m_size(0), m_rain()
{

}
	// Create an empty rainfall list.

bool RainfallList::add(unsigned long rainfall)
{
	if (rainfall >= 0 && rainfall <= 400 && m_rain.size() < DEFAULT_MAX_ITEMS) //checks for valid range (0,400) and if rainfall list is full 
	{
		m_rain.insert(rainfall); //inserts into list of rainfall data 
			return true;
	}
	else
		return false; 
}
// If the rainfall is valid (a value from 0 to 400) and the rainfall list
// has room for it, add it to the rainfall list and return true.
// Otherwise, leave the rainfall list unchanged and return false.

bool RainfallList::remove(unsigned long rainfall)
{
	int position = m_rain.find(rainfall);//use find function to find the position at which the "rainfall" instance occurs
	
	//position will be -1 if no specified instance of rainfall is found in the rainfall list 

	return m_rain.erase(position); //erase returns a boolean value so we can just return it to see if a rainfall was removed successfully 
	
}
// Remove one instance of the specified rainfall from the rainfall list.
// Return true if a rainfall was removed; otherwise false.

int RainfallList::size() const
{
	return m_rain.size(); 
}

// Return the number of rainfalls in the list.

unsigned long RainfallList::minimum() const
{
	ItemType minimumValue; //unsigned long type
	if (size() > 0)
	{
		//minimum value should always be at 0th index of the sequence as the add function should add values to the sequence in sequential order 
		m_rain.get(0, minimumValue); //rainfall value at position 0 of the rainfall sequence gets copied into minimumvalue
		return minimumValue; 
	}
	else
		return NO_RAINFALLS;
}
// Return the lowest-valued rainfall in the rainfall list.  If the list is
// empty, return NO_RAINFALLS.

unsigned long RainfallList::maximum() const
{
	ItemType maximumValue; //unsigned long type
	if (size() > 0)
	{
		m_rain.get(m_rain.size() - 1, maximumValue);
		return maximumValue;
	}
	else
		return NO_RAINFALLS;
}
// Return the highest-valued rainfall in the rainfall list.  If the list is
// empty, return NO_RAINFALLS.