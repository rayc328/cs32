// Dictionary.cpp
#include "Dictionary.h"
#include <string>
#include <list>
#include <vector>
#include <functional>
#include <cctype>
#include <algorithm>
#include <utility>  
using namespace std;

void removeNonLetters(string& s);

class DictionaryImpl
{
public:
    DictionaryImpl(int maxBuckets) : m_maxBuckets(maxBuckets), m_words(maxBuckets, list<string>()) //create a vector of empty lists
    {}
    ~DictionaryImpl()
    {}
    void insert(string word);
    void lookup(string letters, void callback(string)) const;
    int hashFunction(string word) const;
private:
    vector<list<string>> m_words; //using chaining to deal with collisions 
    int m_maxBuckets; 
};

int DictionaryImpl::hashFunction(string word) const
{
   hash<string> stringHash;
   return stringHash(word) % m_maxBuckets; 
}

void DictionaryImpl::insert(string word)
{ 
    removeNonLetters(word); //remove nonletters before using hash function
    string sortWord = word; 

    if (!word.empty()) //make sure string isnt empty before we perform hash function 
    {
        sort(sortWord.begin(), sortWord.end());
        int hashValue = hashFunction(sortWord);
        m_words[hashValue].push_back(word);
    }
}

void DictionaryImpl::lookup(string letters, void callback(string)) const
{
    if (callback == nullptr) //incase of invalid callback function
        return;

    removeNonLetters(letters);
    if (letters.empty())
        return; 

    sort(letters.begin(), letters.end());
    int hashValue = hashFunction(letters); 

    const list<string>& anagramsList = m_words[hashValue];

    for (list<string>::const_iterator word = anagramsList.begin(); word != anagramsList.end(); ++word)
    {
        string isAnagram = *word; 
        sort(isAnagram.begin(), isAnagram.end()); //sort the words in the list and compare them to the word we are looking for, we do this to account for collisions

        if (isAnagram == letters)
        {
            callback(*word);
        }
    }
}

void removeNonLetters(string& s)
{
    string::iterator to = s.begin();
    for (string::const_iterator from = s.begin(); from != s.end(); from++)
    {
        if (isalpha(*from))
        {
            *to = tolower(*from);
            to++;
        }
    }
    s.erase(to, s.end());  // chop everything off from "to" to end.
}

//******************** Dictionary functions ******************************

// These functions simply delegate to DictionaryImpl's functions

Dictionary::Dictionary(int maxBuckets)
{
    m_impl = new DictionaryImpl(maxBuckets);
}

Dictionary::~Dictionary()
{
    delete m_impl;
}

void Dictionary::insert(string word)
{
    m_impl->insert(word);
}

void Dictionary::lookup(string letters, void callback(string)) const
{
    m_impl->lookup(letters, callback);
}
