
void listAll(const MenuItem* m, string path) // two-parameter overload
{
    if (m == nullptr)
        return;

    if (m->name() != "")
        cout << path << m->name() << endl;

    if (m->menuItems() == nullptr || m->menuItems()->size() == 0) //check for Plainmenuitem 
        return;

    if (m->name() != "")
    {
        path += m->name() + "/";
    }

    for (int i = 0; i < m->menuItems()->size(); i++)
    {
        const vector<MenuItem*>* items = m->menuItems(); 
        listAll((*items)[i], path);
    }
}
