#include <iostream>
using namespace std; 

#include "Sequence.h"

Sequence::Sequence() : m_size(0)
{
	dummy.next = &dummy; //creating double circular linked list, next and previous pointers of the dummy node point to dummy node itself
	dummy.prev = &dummy; 
}

Sequence::Sequence(const Sequence& sequenceToCopy) : m_size(0) //copy constructor 
{
	dummy.next = &dummy; //intialize new dummy node as we are creating a copy of the linked list 
	dummy.prev = &dummy; 

	ItemType value;
	for (int i = 0; i < sequenceToCopy.size(); i++)
	{
		sequenceToCopy.get(i, value); //get values from other sequence 
		this->insert(i, value); //insert values into the copy we are making 
	}
}

Sequence::~Sequence() //destructor 
{
	Node* tracker = dummy.next; 
	Node* toBeDestroyed = tracker; //set toBeDestroyed pointer to where tracker is pointing 
	while (tracker != &dummy)
	{
		tracker = tracker->next; // the tracker pointer helps us iterate through the entire list while the toBeDestroyed pointer allows us to deallocate each node 
		delete toBeDestroyed; 
		toBeDestroyed = tracker; 
	}
 
	dummy.next = &dummy; //dummy node isn't dynamically allocated so we set the pointers back to itself as we are utilizing a circular doubly linked list 
	dummy.prev = &dummy;//prevents dangling pointer 
	m_size = 0; 
}

Sequence& Sequence::operator=(const Sequence& src) //assignment operator
{
	if (this == &src) //check for aliasing
		return *this; 
	else
	{
		for (int i = this->m_size - 1; i >= 0; i--) //have to delete items backwards 
		{
			erase(i); //erasing all the nodes in the sequence we want to copy to 
		}

		ItemType value;
		this->m_size = 0; //set this->size to 0 because it is empty at this stage, size will increment itself everytime we call the insert function in the latter for loop 
		for (int i = 0; i < src.size(); i++)
		{
			src.get(i, value);
			this->insert(i, value);
		}
		return *this;
	}
}

//get values from src linkedlist and insert them into new linked list

bool Sequence::empty() const
{
	if (size() == 0)
		return true;
	else
		return false; 
}

int Sequence::size() const
{
	return m_size; 
}

int Sequence::insert(int pos, const ItemType& value)
{
	//allocating new memory for the node we want to insert and then adjusting the pointers, implementations for inserting a new node have a common pattern:
		//1. allocating new memory   
		//2. setting the value of the newly allocated node  
		//3. My implementation requires the adjustment of 4 different pointers since we have a circular doubly linked list 
	if (pos < 0 || pos > size())
		return -1;

	if (pos == 0) //inserting an item at the beginning of linked list, works for empty and non empty linked list 
	{
		Node* newNode = new Node;
		newNode->value = value;
		newNode->next = dummy.next;
		newNode->prev = &dummy;
		newNode->next->prev = newNode;
		dummy.next = newNode;
		m_size++;
		return pos;
	}

	if (pos == size()) //inserting an item at the end of the linked list when the linkedlist IS NOT EMPTY
	{
		Node* newNode = new Node;
		newNode->value = value;
		newNode->next = &dummy;
		newNode->prev = dummy.prev;
		dummy.prev->next = newNode;
		dummy.prev = newNode;
		m_size++;
		return pos;
	}

	//inserting an item in the middle of the linkedlist 
	Node* tracker = &dummy; //have a pointer to dummynode so we can access the nodes after dummy and essentially iterate through the linked list 
	for (int i = 0; i < pos; i++)
	{
		tracker = tracker->next;
	}

	Node* newNode = new Node;
	newNode->value = value;
	newNode->next = tracker->next;
	newNode->prev = tracker;
	tracker->next = newNode;
	newNode->next->prev = newNode;
	m_size++;
	return pos;
}

int Sequence::insert(const ItemType& value)
{
	//allocating new memory for the node we want to insert and then adjusting the pointers, implementations for inserting a new node have a common pattern:
		//1. allocating new memory   
		//2. setting the value of the newly allocated node  
		//3. My implementation requires the adjustment of 4 different pointers since we have a circular doubly linked list 
	if (size() == 0)
	{
		Node* newNode = new Node; 
		newNode->value = value;
		newNode->next = dummy.next;
		newNode->prev = &dummy;
		dummy.prev = newNode;
		dummy.next = newNode;
		m_size++;
		return 0; //return 0 because the node will always be inserted at index 0 when the sequence is empty 
	}

	Node* tracker = &dummy;

	for (int p = 0; p < size(); p++)
	{
		tracker = tracker->next;
		if (value <= tracker->value) //insert node 1 position after position of tracker 
		{
			Node* newNode = new Node; 
			newNode->value = value; 
			newNode->next = tracker;
			newNode->prev = tracker->prev;
			tracker->prev->next = newNode; 
			tracker->prev = newNode; 
			m_size++;
			return p;
		}
	}

	//if the value being inserted is greater than all existing items in the sequence --> inserting item at the end of the sequence 
	Node* newNode = new Node;
	newNode->value = value;
	newNode->next = &dummy;
	newNode->prev = dummy.prev;
	dummy.prev->next = newNode;
	dummy.prev = newNode; 
	m_size++;
	return (size() - 1); 
}

bool Sequence::erase(int pos)
{
	if (pos >= 0 && pos < size())
	{
		Node* tracker = &dummy; 
		for (int position = 0; position < pos; position++)
		{
			tracker = tracker->next; //tracker will be pointing at the node BEFORE the node we want to delete 
		}

		Node* kill = tracker->next; //points to the node we want to delete 
		tracker->next = kill->next; 
		kill->next->prev = tracker;
		delete kill; //deletes node at pos
		m_size--; 
		return true; 
	}
	else
		return false; 
}

int Sequence::remove(const ItemType& value)
{
	if (size() == 0)
		return 0; 

	Node* tracker = &dummy; 
	int valuesRemoved = 0;

	while (tracker->next != &dummy) //since our linked list is circular in nature, we want to make sure we only iterate through once
	{
		if (tracker->next->value == value)
		{
			Node* kill = tracker->next; //have a pointer "kill" that points to the node we want to delete 
			tracker->next = kill->next;
			kill->next->prev = tracker;
			delete kill;
			m_size--;
			valuesRemoved++;
		}
		else
		{
			tracker = tracker->next;
		}
	}

	return valuesRemoved; 
}

bool Sequence::get(int pos, ItemType& value) const
{
	if (pos >= 0 && pos < size())
	{
		Node* tracker = dummy.next; 
		for (int i = 0; i < pos; i++)
		{
			tracker = tracker->next;  //tracker will end up at the position of the node that we want to copy the value from 
		}
		value = tracker->value; 
		return true; 
	}
	else
		return false; 
}

bool Sequence::set(int pos, const ItemType& value)
{
	if (pos >= 0 && pos < size())
	{
		Node* tracker = dummy.next;
		{
			for (int i = 0; i < pos; i++)
			{
				tracker = tracker->next;  //tracker will end up at the position of the node that we want to change the value of 
			}
			tracker->value = value;
			return true;
		}
	}
	else 
		return false; 
}

int Sequence::find(const ItemType& value) const
{
	Node* tracker = dummy.next; //create pointer that we can use to iterate through the sequence

	for (int p = 0; p < size(); p++)
	{
		if (tracker->value == value) //as soon as we find a value that matches the value passed into the function we will return the position and exit
		{
			return p;
		}
		tracker = tracker->next; //if no matching value is found we will continue iterating through the sequence 
	}
	return -1; //no matching value in the sequence was found 
}

void Sequence::swap(Sequence& other)
{
	Sequence temp = other; //we can do this because we defined our own assignment operator 
	other = *this;
	*this = temp; 
}

void Sequence::dump() const 
{
	Node* bruh = dummy.next; 
	while (bruh != &dummy)
	{
		cerr << bruh->value << endl; 
		bruh = bruh->next; 
	}
	cerr << endl;
}

/////////////////////////////////////////////////////////
//////
//////        Sequence algorithm implementations 
/////
///////////////////////////////////////////////////////////

int subsequence(const Sequence& seq1, const Sequence& seq2) 
{
	int seq1Size = seq1.size();
	int seq2Size = seq2.size();
	
	if (seq1Size == 0 || seq2Size == 0 || seq2Size > seq1Size) //seq2 would not be a subsequence of seq1 if it were greater in size 
	{
		return -1;
	}

	ItemType firstValue;
	seq2.get(0, firstValue); //storing 0th index value of seq2 so we can compare it with values of seq1

	for (int i = 0; i <= seq1Size - seq2Size; i++) 
	{
		ItemType seq1Value;
		seq1.get(i, seq1Value);
		if (seq1Value == firstValue) 
		{
			bool match = true;
			for (int j = 1; j < seq2Size; j++) //comparing the rest of seq2 values with seq1 values 
			{
				ItemType seq2Value;
				seq2.get(j, seq2Value); 
				seq1.get(i + j, seq1Value); //checking the position in sequence 1 AFTER where first matching value was found
				if (seq1Value != seq2Value) 
				{
					match = false; 
					break; //leave the nested for loop to continue searching for a matching value in the outer for loop 
				}
			}
			if (match == true) //if we iterate through and find that the consecutive values match then we return the index at which the first value matched (index i)
			{
				return i;
			}
		}
	}
	return -1;
}

//edge case: sequence 2 greater than sequence 1 
//aliasing 

void concatReverse(const Sequence& seq1, const Sequence& seq2, Sequence& result)
{
	if (result.empty() == false)
	{
		for (int i = result.size() - 1; i >= 0; i--) //traverse backwards through the linked list and delete all nodes of the result sequence 
		{
			result.erase(i); 
		}
	}

	ItemType seq1Value;
	int seq1Index; 
	for (seq1Index = seq1.size() - 1; seq1Index >= 0; seq1Index--) //grab the values in reverse order but insert them in the flipped order 
	{
		seq1.get(seq1Index, seq1Value); //starts by grabbing last value of seq1
		result.insert((seq1.size() - (seq1Index+1)), seq1Value); //inserting them into result requence in flipped order of how they were in sequence1
	}
	
	ItemType seq2Value;
	int seq2Index; 
	int resultSize = result.size(); //we want to use the size of result sequence so we know where to insert the values of seq2
	for (seq2Index = seq2.size() - 1; seq2Index >= 0; seq2Index--)
	{
		seq2.get(seq2Index, seq2Value); //traverse backwards through sequence2 
		result.insert(resultSize, seq2Value);
		resultSize++; 
	}
}
