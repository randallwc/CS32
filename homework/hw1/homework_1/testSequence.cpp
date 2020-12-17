#include "Sequence.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    Sequence a;
    ItemType x;
    assert(a.empty() == 1);
    assert(a.size() == 0);
    assert(a.insert(100, 800) == -1);
    assert(a.insert(0,30) == 0);
    assert(a.insert(1,50) == 1);
    assert(a.insert(2,77) == 2);
    assert(a.insert(3,55) == 3);
    assert(a.insert(4,22) == 4);
    assert(a.size() == 5);

    assert(a.insert(5,30) == 5);
    assert(a.remove(30) == 2);
    assert(a.remove(203230283028) == 0);
    assert(a.size() == 4);

    assert(a.erase(5) == 0);
    assert(a.erase(0) == 1);
    assert(a.size() == 3);

    a.erase(0);
    a.erase(0);
    a.erase(0);
    assert(a.empty() == 1);

    a.insert(0,122);
    a.insert(1,10223);
    a.insert(2,10);
    a.insert(3,1053);
    a.insert(4,1033);
    assert(a.erase(5) == 0);

    a.get(2, x);
    assert(x == 10);

    assert(a.get(232, x) == 0);
    assert(x == 10);

    assert(a.set(5, 69420) == 0);
    assert(a.set(2, 69420) == 1);
    a.get(2,x);
    assert(x == 69420);

    assert(a.find(1053) == 3);
    assert(a.find(22232223) == -1);
    a.insert(5, 10223);
    assert(a.find(10223) == 1);
    assert(a.remove(10223) == 2);
    assert(a.size() == 4);
    assert(a.insert(999999) == 4);
    assert(a.insert(500) == 1);

    Sequence b;
    assert(b.empty() == 1);
    b.insert(1);//0
    b.insert(2);//1
    b.insert(3);//2
    b.insert(4);//3
    b.insert(5);//4
    b.insert(6);//5
    b.insert(7);//6
    b.insert(8);//7

    Sequence c;
    assert(c.empty() == 1);
    c.insert(5);//0
    c.insert(10);//1
    c.insert(15);//2
    c.insert(20);//3
    c.insert(25);//4
    c.insert(30);//5
    c.insert(35);//6
    c.insert(40);//7
    c.insert(45);//8

    c.swap(b);
    assert( c.find(8) == 7);
    assert( c.find(5) == 4);
    assert( c.find(1) == 0);

    b.swap(c);
    assert( c.find(5) == 0);
    assert( c.find(40) == 7);
    assert( b.find(7) == 6);
    
    Sequence z;
    assert(z.empty() == 1);
    z.insert(10);
    z.insert(10);
    z.insert(10);
    z.insert(10);
    z.insert(10);
    z.insert(10);
    z.insert(420);
    z.insert(420);
    z.insert(500);
    z.insert(5);
    z.insert(20);
    assert(z.remove(10) == 6);
    assert(z.find(5) == 0);
    assert(z.find(20) == 1);
    assert(z.find(420) == 2);
    assert(z.find(500) == 4);
    
    assert(z.size() == 5);
    assert(z.remove(420) == 2);
    
    cerr << "all tests passed"<<endl;
    return 0;
}
