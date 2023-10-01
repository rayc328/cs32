// Remove the even integers from li.
// It is acceptable if the order of the remaining even integers is not
// the same as in the original list.
void removeEven(list<int>& li)
{
	list<int>::iterator i = li.begin(); 
	while (i != li.end())
	{
		if (*i % 2 == 0) // checking for even number
		{
			i = li.erase(i);
		}
		else
			i++;
	}
}