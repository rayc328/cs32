// Return false if the somePredicate function returns false for at
// least one of the array elements; return true otherwise.
bool allTrue(const string a[], int n)
{
    if (n <= 0)
        return true;

    if (n == 1)
        return !somePredicate(a[0]);  //if somePredicate is true that means there was an empty string, thus we want to return false in the allTrue function 

    return allTrue(a + 1, n - 1) && !somePredicate(a[0]); 
}  

// Return the number of elements in the array for which the
// somePredicate function returns true.
int countTrue(const string a[], int n) //returns the number of empty items in an array of strings 
{
    if (n <= 0)
        return 0; 

    int numberTrue = countTrue(a + 1, n - 1);
    return numberTrue + somePredicate(a[0]);
}

// Return the subscript of the first element in the array for which
// the somePredicate function returns true.  If there is no such
// element, return -1.
int firstTrue(const string a[], int n)
{
    if (n <= 0)
        return -1;

    if (somePredicate(a[0]) == true)
        return 0; 
   
    int pos = firstTrue(a + 1, n - 1);  
    return pos + 1;
} 

// Return the subscript of the first string in the array that is >= all
// strings in the array (i.e., return the smallest subscript m such
// that a[m] >= a[k] for all k from 0 to n-1).  If the function is told
// that no strings are to be considered to be in the array, return -1.
int positionOfMax(const string a[], int n)
{
    if (n <= 0)
        return -1; 

    else if (n == 1)
        return 0;

    int firstHalfMax = positionOfMax(a, n / 2);
    int secondHalfMax = positionOfMax(a + (n / 2), n - (n / 2)) + n/2; //need to add n/2 because the index returned from our "magic function" is relative to the substring
    
    if (a[firstHalfMax] >= a[secondHalfMax])
    {
        return firstHalfMax;
    }
    else
        return secondHalfMax; 
} 

// If all n2 elements of a2 appear in the n1 element array a1, in
// the same order (though not necessarily consecutively), then
// return true; otherwise (i.e., if the array a1 does not include
// a2 as a not-necessarily-contiguous subsequence), return false.
// (Of course, if a2 is empty (i.e., n2 is 0), return true.)
// For example, if a1 is the 7 element array
//    "john" "sonia" "elena" "ketanji" "sonia" "elena" "samuel"
// then the function should return true if a2 is
//    "sonia" "ketanji" "samuel"
// or
//    "sonia" "elena" "elena"
// and it should return false if a2 is
//    "sonia" "samuel" "ketanji"
// or
//    "john" "ketanji" "ketanji"
bool contains(const string a1[], int n1, const string a2[], int n2)
{
    if (n2 <= 0) //if array2 is empty
        return true; 
   
    if (n1 < n2 || n1 <= 0) //array 1 cannot be smaller than array 2, array1 cannot be empty either 
        return false; 

    bool contain = contains(a1 + 1, n1 - 1, a2 + 1, n2 - 1);

    if (a1[0] == a2[0])
        return contain;
    else
        return contains(a1+1, n1-1, a2, n2); //contain searching for a match with a2 thus we do not increment a2 or n2 
}
