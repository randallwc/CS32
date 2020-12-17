void removeBad(list<Movie*>& li)
{
    list<Movie*>::iterator it = li.begin();
    while(it != li.end())
    {
        if ((*it)->rating() < 55)
        {
            list<Movie*>::iterator temp = it;
            delete *temp;
            it = li.erase(it);
        }
        else
            it++;
    }
}
