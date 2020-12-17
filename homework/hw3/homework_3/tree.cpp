//For this part of the homework, you will turn in one file named tree.cpp that contains the four functions above and nothing more.


int countIncludes(const string a1[], int n1, const string a2[], int n2)
{
    if( n2 <= 0 )// if second is 0 or -
        return 1;
    if( n1 < 0 )// if first - return 0
        return 0;
    
    if(n1 == 1 && n2 == 1 && a1[0] == a2[0]) // if they are both 1 and match first arr elements
        return 1;
    
    if(n1 == 1 && n2 > 1) // if first is one element but other is bigger then return 0
        return 0;
    
    if(a1[0] == a2[0])// found match so try next in both arrays and
        //start another recursion to add up
    {
        return countIncludes(a1+1,n1-1,a2+1,n2-1) + countIncludes(a1+1,n1-1,a2,n2);
    }
    
    // didn't match so try next in first arr
    return countIncludes(a1+1,n1-1,a2,n2);

}

void exchange(string& x, string& y)
{
    string t = x;
    x = y;
    y = t;
}

void separate(string a[], int n, string separator, int& firstNotLess, int& firstGreater)
{
    if (n < 0)
        n = 0;
    
    // It will always be the case that just before evaluating the loop
    // condition:
    //  firstNotLess <= firstUnknown and firstUnknown <= firstGreater
    //  Every element earlier than position firstNotLess is < separator
    //  Every element from position firstNotLess to firstUnknown-1 is
    //    == separator
    //  Every element from firstUnknown to firstGreater-1 is not known yet
    //  Every element at position firstGreater or later is > separator
    
    firstNotLess = 0;
    firstGreater = n;
    int firstUnknown = 0;
    while (firstUnknown < firstGreater)
    {
        if (a[firstUnknown] > separator)
        {
            firstGreater--;
            exchange(a[firstUnknown], a[firstGreater]);
        }
        else
        {
            if (a[firstUnknown] < separator)
            {
                exchange(a[firstNotLess], a[firstUnknown]);
                firstNotLess++;
            }
            firstUnknown++;
        }
    }
}

void order(string a[], int n)
{
    if(n <= 1)
        return;
    int fnl, fg;
    separate(a, n, a[n/2], fnl, fg);
    order(a , fnl); // order from a to first not less
    order(a+fg, n-fg); // order from first not greater to end
}
