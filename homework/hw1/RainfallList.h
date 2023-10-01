#ifndef RainfallList_H
#define RainfallList_H

#include <limits>

#include "Sequence.h"

const unsigned long NO_RAINFALLS = std::numeric_limits<unsigned long>::max();

class RainfallList
{
public:
    RainfallList();       // Create an empty rainfall list.

    bool add(unsigned long rainfall);
    // If the rainfall is valid (a value from 0 to 400) and the rainfall list
    // has room for it, add it to the rainfall list and return true.
    // Otherwise, leave the rainfall list unchanged and return false.

    bool remove(unsigned long rainfall);
    // Remove one instance of the specified rainfall from the rainfall list.
    // Return true if a rainfall was removed; otherwise false.

    int size() const;  // Return the number of rainfalls in the list.

    unsigned long minimum() const;
    // Return the lowest-valued rainfall in the rainfall list.  If the list is
    // empty, return NO_RAINFALLS.

    unsigned long maximum() const;
    // Return the highest-valued rainfall in the rainfall list.  If the list is
    // empty, return NO_RAINFALLS.

private:
    Sequence m_rain; //sequence of rainfall data 
    int m_size;

    // Some of your code goes here.
};

#endif