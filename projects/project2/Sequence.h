#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <iostream>
#include <string> 

using ItemType = std::string; //using type alias 

class Sequence
{
private:
    struct Node
    {
        ItemType value; //value stored in the node
        Node* next; //pointer to predecessor
        Node* prev; //pointer to successor 
    };

    int m_size;
    Node dummy; 

public:

    //constructor
    Sequence(); 
   
    //destructor
    ~Sequence(); 

    //copy constructor
    Sequence(const Sequence& sequenceToCopy);
   
    //assignment operator 
    Sequence& operator=(const Sequence& src); 

    bool empty() const;  // Return true if the sequence is empty, otherwise false.

    int size() const;    // Return the number of items in the sequence.

    int insert(int pos, const ItemType& value);

    int insert(const ItemType& value);

    bool erase(int pos);

    int remove(const ItemType& value);
   
    bool get(int pos, ItemType& value) const;

    bool set(int pos, const ItemType& value);

    int find(const ItemType& value) const;

    void swap(Sequence& other);
    // Exchange the contents of this sequence with the other one.

    void dump() const;

};

/////////////////////////////////////////////////////////
//////
//////        Sequence algorithms
/////
///////////////////////////////////////////////////////////

int subsequence(const Sequence& seq1, const Sequence& seq2);
void concatReverse(const Sequence& seq1, const Sequence& seq2, Sequence& result);

#endif

