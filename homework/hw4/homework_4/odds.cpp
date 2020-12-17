void removeOdds(vector<int>& v)
{
    for(int i = 0; i < v.size(); i++)
    {
        if(v.at(i) % 2 != 0)
        {
            v.erase(v.begin() + i);
            i--;
        }
    }
}
