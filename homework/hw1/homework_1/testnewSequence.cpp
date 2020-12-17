#include "newSequence.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    Sequence cats(2);
    assert(cats.insert(100) == 0);
    assert(cats.insert(202) == 1);
    assert(cats.size() == 2);
    ItemType x;
    assert(cats.get(0, x)  &&  x == 100);
    assert(cats.get(1, x)  &&  x == 202);
    assert(cats.insert(2) == -1);

    assert(cats.erase(1) == 1);
    assert(cats.remove(100) == 1);
    assert(cats.empty() == 1);
    cats.insert(10);
    cats.insert(9);
    assert(cats.find(10) == 1);
    assert(cats.set(1, 69) == 1);
    assert(cats.set(3,420) == 0);
    assert(cats.empty() == 0);

    Sequence a(1000);   // a can hold at most 1000 items
    Sequence b(5);      // b can hold at most 5 items
    Sequence c;         // c can hold at most DEFAULT_MAX_ITEMS items
    ItemType v = 10;


    for (int i = 0; i < DEFAULT_MAX_ITEMS; i++)
    {
        assert(c.insert(v) == 0);
    }
    assert(c.insert(11) == -1);

    // No failures inserting 5 items into b
    for (int k = 0; k < 5; k++)
    {
         assert(b.insert(v) != -1);
    }

    // Failure if we try to insert a sixth item into b
    assert(b.insert(v) == -1);

    // When two Sequences' contents are swapped, their capacities are
    // swapped as well:
    a.swap(b);
    assert(a.insert(v) == -1  &&  b.insert(v) != -1);
    
    Sequence z;
    assert(z.empty() == 1);
    z.insert(10);
    z.insert(10);
    z.insert(10);
    z.insert(10);
    z.insert(10);
    z.insert(5);
    z.insert(20);
    assert(z.size() == 7);
    assert(z.remove(10) == 5);
    assert(z.size() == 2);
    assert(z.find(5) == 0);
    assert(z.find(20) == 1);
    assert(z.empty() == 0);
    z.erase(0);
    z.erase(0);
    assert(z.empty() == 1);

    cerr << "all tests passed" << endl;

    return 0;
}
