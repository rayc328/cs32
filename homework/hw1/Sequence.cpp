#include <iostream>
using namespace std; 

//header file
#include "Sequence.h"

Sequence::Sequence() : mSequenceSize(0), mSequence()
{
}

bool Sequence::empty() const
{
	if (mSequenceSize == 0)
		return true;
	else
		return false; 
}

int Sequence::size() const
{
	return mSequenceSize; 
}

int Sequence::insert(int pos, const ItemType& value)
{
	if (pos < 0 || pos > mSequenceSize || mSequenceSize == DEFAULT_MAX_ITEMS) //size cannot be 160 as that would be out of bounds of the array
	{
		return -1;
	}
	if (size() == pos) 
	{
		mSequence[pos] = value; //pos equaling size() means that a value is inserted at the very end, eg insert at index 10, size 10 item (index 0 - 9)
		if (size() < DEFAULT_MAX_ITEMS) //if size is 160 then we just replace the last index (159) with "value" but there is nothing to shift to the right so size remains the same 
		{
			mSequenceSize++;
		}
		return pos; 
	}
	else 
	{
		mSequenceSize++; //increase sequence size since we added one item 
		for (int i = mSequenceSize - 1; i > pos; i--)
		{
			mSequence[i] = mSequence[i - 1]; 
		}
		mSequence[pos] = value;  
	}
	return pos;
}

int Sequence::insert(const ItemType& value)
{
	if (mSequenceSize >= DEFAULT_MAX_ITEMS)
	{
		return -1; 
	}
	else
	{
		for (int i = 0; i < mSequenceSize; i++)
		{
			if (value <= mSequence[i])
			{
				mSequenceSize++;
				for (int k = mSequenceSize - 1; k > i; k--)
				{
					mSequence[k] = mSequence[k - 1];
				}
				mSequence[i] = value;
				return i; //index at which value was inserted
			}
		}
		//if the entire for loop runs and value is not less than or equal to any of the indexes in the sequence, then we insert the value at the end
		mSequenceSize++;
		mSequence[mSequenceSize - 1] = value; //decrease mSequenceSize by 1 because we incremented mSequenceSize
		return (mSequenceSize - 1);
	}
}

// Let p be the smallest integer such that value <= the item at
// position p in the sequence; if no such item exists (i.e.,
// value > all items in the sequence), let p be size().  Insert
// value into the sequence so that it becomes the item in position
// p.  The original item in position p and those that follow it end
// up at positions one greater than before.  Return p if the value
// was actually inserted.  Return -1 if the value was not inserted
// (perhaps because the sequence has a fixed capacity and is full).


bool Sequence::erase(int pos) 
{
	if (pos < 0 || pos >= size())
	{
		return false; 
	} 
	else
	{ 
		for (int i = pos; i < mSequenceSize - 1; i++)
		{
			mSequence[i] = mSequence[i + 1];
		}
		mSequenceSize--;
		return true; 
	}
}

//1 2 3 4 5 6 7 8 9 10 
//2 3 4 5 6 7 8 9 10 10 

// If 0 <= pos < size(), remove the item at position pos from
// the sequence (so that all items that followed that item end up at
// positions one lower than they were at before), and return true.
// Otherwise, leave the sequence unchanged and return false.

int Sequence::remove(const ItemType& value)
{
	int removeCounter = 0;
	for (int i = 0; i < mSequenceSize; i++)
	{
		if (mSequence[i] == value)
		{
			for (int k = i; k < mSequenceSize && k < DEFAULT_MAX_ITEMS - 1; k++)
			{
				mSequence[k] = mSequence[k + 1];
			}
			removeCounter++;
			mSequenceSize--;
			i--; //basically have to check every index twice to check if the item shifted left == value
		}
	}
	return removeCounter; 
}

// Erase all items from the sequence that == value.  Return the
// number of items removed (which will be 0 if no item == value).

bool Sequence::get(int pos, ItemType& value) const
{
	if (pos >= 0 && pos < size())
	{
		value = mSequence[pos];
		return true; 
	}
	else
		return false; 
}
// If 0 <= pos < size(), copy into value the item in position pos
// of the sequence and return true.  Otherwise, leave value unchanged
// and return false.

bool Sequence::set(int pos, const ItemType& value)
{
	if (pos >= 0 && pos < size())
	{
		mSequence[pos] = value;
		return true;
	}
	else
		return false;
}

// If 0 <= pos < size(), replace the item at position pos in the
// sequence with value and return true.  Otherwise, leave the sequence
// unchanged and return false.

int Sequence::find(const ItemType& value) const
{
	for (int p = 0; p < mSequenceSize; p++)
	{
		if (mSequence[p] == value)
		{
			return p;
		}
	}
	return -1;
}
// Let p be the smallest integer such that value == the item at
// position p in the sequence; if no such item exists, let p be -1.
// Return p.

void Sequence::swap(Sequence& other)
{
	ItemType tempSequence[DEFAULT_MAX_ITEMS]; //creating temp array to store our sequence
	
	int tempSequenceSize = mSequenceSize; 
	mSequenceSize = other.mSequenceSize;
	other.mSequenceSize = tempSequenceSize; 

	for (int i = 0; i < DEFAULT_MAX_ITEMS; i++)
	{
		tempSequence[i] = mSequence[i];
		mSequence[i] = other.mSequence[i];
		other.mSequence[i] = tempSequence[i];
	}
}

// Exchange the contents of this sequence with the other one.

void Sequence::dump() const {
	cerr << "Size: " << mSequenceSize << endl;
	for (int i = 0; i < mSequenceSize; i++) {
		cerr << mSequence[i] << endl;
	}
}