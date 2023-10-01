#include <iostream>
using namespace std;

//header file
#include "newSequence.h"

Sequence::Sequence() : mSequenceSize(0), arrayCapacity(DEFAULT_MAX_ITEMS) //default constructor
{
	mSequence = new ItemType[DEFAULT_MAX_ITEMS];
}

Sequence::Sequence(int arraySize): mSequenceSize(0), arrayCapacity(arraySize) //constructor to create dynamic array
{
	mSequence = new ItemType[arraySize];
}

Sequence::~Sequence() //destructor 
{
	delete[] mSequence; 
}

Sequence& Sequence::operator=(const Sequence& src) //assignment operator
{
	if (&src == this) //check for aliasing 
		return *this;
	else
	{
		delete[] mSequence; 
		mSequenceSize = src.mSequenceSize;
		mSequence = new ItemType[mSequenceSize];
		for (int i = 0; i < mSequenceSize; i++)
		{
			mSequence[i] = src.mSequence[i];
		}
		return *this; 
	}
}

Sequence::Sequence(const Sequence& sequenceToCopy) //copy constructor 
{
	arrayCapacity = sequenceToCopy.arrayCapacity; //initialize arrayCapacity?
	mSequenceSize = sequenceToCopy.mSequenceSize;
	mSequence = new ItemType[mSequenceSize];
	for (int i = 0; i < mSequenceSize; i++)
	{
		mSequence[i] = sequenceToCopy.mSequence[i];
	}
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
	if (pos < 0 || pos > mSequenceSize || mSequenceSize == arrayCapacity) //Sequence Size == array capacity indicates that array is full 
	{
		return -1;
	}
	if (size() == pos)
	{
		mSequence[pos] = value; //pos equaling size() means that a value is inserted at the very end, eg insert at index 10, size 10 item (index 0 - 9)
		if (size() < arrayCapacity) //if size is 160 then we just replace the last index (159) with "value" but there is nothing to shift to the right so size remains the same 
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
	if (mSequenceSize >= arrayCapacity)
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

int Sequence::remove(const ItemType& value)
{
	int removeCounter = 0;
	for (int i = 0; i < mSequenceSize; i++)
	{
		if (mSequence[i] == value)
		{
			for (int k = i; k < mSequenceSize && k < arrayCapacity - 1; k++)
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

void Sequence::swap(Sequence& other)
{
	int tempArrayCapacity = other.arrayCapacity; //array capacity 
	other.arrayCapacity = arrayCapacity;
	arrayCapacity = tempArrayCapacity;

	int tempSequenceSize; //swap sequence size
	tempSequenceSize = other.mSequenceSize;
	other.mSequenceSize = mSequenceSize;
	mSequenceSize = tempSequenceSize;

	ItemType* tempSequence; //swap items of the sequence
	tempSequence = other.mSequence;
	other.mSequence = mSequence; 
	mSequence = tempSequence; 

	//implemented assignment operator so we can just use "="
}

// Exchange the contents of this sequence with the other one.

void Sequence::dump() const {
	cerr << "Size: " << mSequenceSize << endl;
	for (int i = 0; i < mSequenceSize; i++) {
		cerr << mSequence[i] << endl;
	}
}