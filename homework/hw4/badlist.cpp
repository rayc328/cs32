void removeBad(list<Restaurant*>& li) //list of pointers of restauraunt type 
{
	list<Restaurant*>::iterator i = li.begin(); //iterator points to the restaurant pointers 
	while (i != li.end())
	{
		if ((*i)->stars() <= 2)
		{
			delete* i; 
			i = li.erase(i);
		}
		else
			i++;
	}
}

