//you will turn in one file named linear.cpp that contains the five functions and nothing more: no #include directives, no using namespace std;, no implementation of somePredicate and no main routine.

bool allTrue(const string a[], int n)
{
    if ( n <= 0 )// bad input
    {
        return true;
    }
    else if (n == 1)// last element
    {
        return somePredicate(a[0]);
    }
    else
    {
        return somePredicate(a[0]) // checks if at position is true
        && allTrue(a+1,n-1); // recursion to check the next position
    }
}

int countFalse(const string a[], int n)
{
    if(n <= 0)
        return 0;
    else if ( n == 1 )
    {
        return !somePredicate(a[0]);
    }
    else
    {
        return !somePredicate(a[0]) + countFalse(a+1, n-1);
    }
}

int firstFalse(const string a[], int n)
{
    if ( n <= 0 )
        return -1;

    if(!somePredicate(a[0])) // if first is false return the 0 position
        return 0;

    if(firstFalse(a+1, n-1) == -1) // if first false is -1 return -1
        return -1;

    return firstFalse(a + 1, n - 1) + 1; // if it found a

}

int indexOfLeast(const string a[], int n)
{
    if(n <= 0)
        return -1;

    if(n == 1)
        return 0;
    
    int biggest = 1 + indexOfLeast(a+1, n-1);
    
    if(a[0] <= a[biggest])
        return 0;
    
    return biggest;
}

bool includes(const string a1[], int n1, const string a2[], int n2)
{
    if(n2 <= 0)  // if n2 is less than or = 0 its true
        return true;
    if(n2 > 0 && n1 <= 0) // if n2 is greater than 0 and n1 is 0 or neg then its false
        return false;
    
    if(a1[0] == a2[0])
        return includes(a1+1,n1-1,a2+1,n2-1);
    
    return includes(a1+1,n1-1,a2,n2);
}
