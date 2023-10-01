
void removeBad(vector<Restaurant*>& v)
{
	vector<Restaurant*>::iterator i = v.begin();
	while (i != v.end())
	{
		if ((*i)->stars() <= 2)
		{
			delete* i;
			i = v.erase(i);
		}
		else
			i++;
	}
}