void listAll(const Domain* d, string path) // two-parameter overload
{
    if( d == nullptr )
        return;
    
    if(d->subdomains().size() == 0) // if at bottom of tree
    {
        cout << path << '\n';
        return;
    }
    
    for(int i = 0; i < d->subdomains().size(); i++)
    {
        if (path == "") // if root
            listAll(d->subdomains()[i], d->subdomains()[i]->label());
        else // if not root
            listAll(d->subdomains()[i], d->subdomains()[i]->label() + '.' + path);
    }
}
