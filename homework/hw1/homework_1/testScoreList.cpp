#include "ScoreList.h"
#include "Sequence.h"
#include <iostream>
#include <cassert>
using namespace std;


int main()
{
    ScoreList s;
    assert(s.maximum() == NO_SCORE);
    assert(s.minimum() == NO_SCORE);
    assert(!s.add(101));
    assert(s.add(10));
    s.add(50);
    s.add(99);
    s.add(60);
    s.add(60);
    assert(s.maximum() == 99);
    assert(s.minimum() == 10);
    assert(s.size() == 5);
    assert(s.remove(60) == 1);
    assert(s.remove(99) == 1);
    assert(s.size() == 3);
    assert(s.maximum() == 60);
    assert(s.remove(101) == 0);
    assert(s.remove(69) == 0);

    cerr << "all tests passed" << endl;
    return 0;
}
