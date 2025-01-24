#include <iostream>
#include "TurnoutList.h"
#include <cassert>
using namespace std;

int main()
{
    TurnoutList tl;

    tl.add(1000);
    assert(tl.remove(1000));
    assert(tl.size() == 0);
    tl.add(1000);
    tl.add(100);
    assert(!tl.add(-1));
    assert(!tl.add(1801));
    assert(tl.minimum() == 100);
    assert(tl.maximum() == 1000); //[100,1000]

    TurnoutList tl1 = tl; // [100,1000]
    assert(tl1.maximum() == 1000);
    assert(tl1.size() == 2);

    TurnoutList tl2;
    tl2.add(10);
    tl2.add(10);
    tl2.add(30);
    tl2.remove(10);
    assert(tl2.minimum() == 10); //[10,30]

    tl1 = tl2;
    assert(tl1.minimum() == 10); //[10,30]
}