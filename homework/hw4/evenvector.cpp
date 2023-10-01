
// Remove the even integers from v.
// It is acceptable if the order of the remaining even integers is not
// the same as in the original vector.
void removeEven(vector<int>& v)
{
	vector<int>::iterator i = v.begin(); 
	while (i != v.end())
	{
		if (*i % 2 == 0)
		{
			i = v.erase(i);
		}
		else
			i++; 
	}
}
