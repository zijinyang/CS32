#ifndef TESTNUM
#define TESTNUM 0
#endif

#if TESTNUM == 1

#include "Sequence.h"
#include <string>
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
    Sequence ss;
    ss.insert(0, "lavash");
    ss.insert(0, "tortilla");
    assert(ss.size() == 2);
    ItemType x = "injera";
    assert(ss.get(0, x) && x == "tortilla");
    assert(ss.get(1, x) && x == "lavash");
}

int main()
{
    test();
    cout << "Passed all tests" << endl;
}

#elif TESTNUM == 2

#include "Sequence.h"
#include <iostream>
#include <cassert>
using namespace std;

void test(const Sequence& uls)
{
    assert(uls.size() == 2);
    ItemType x = 999;
    assert(uls.get(0, x) && x == 20);
    assert(uls.get(1, x) && x == 10);
}

int main()
{
    Sequence s;
    s.insert(0, 10);
    s.insert(0, 20);
    test(s);
    cout << "Passed all tests" << endl;
}

#elif TESTNUM == 3

#include "newSequence.h"
#include <string>
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
    Sequence ss;
    ss.insert(0, "lavash");
    ss.insert(0, "tortilla");
    assert(ss.size() == 2);
    ItemType x = "injera";
    assert(ss.get(0, x) && x == "tortilla");
    assert(ss.get(1, x) && x == "lavash");
}

int main()
{
    test();
    cout << "Passed all tests" << endl;
}

#elif TESTNUM == 4

#include "newSequence.h"
#include <iostream>
#include <cassert>
using namespace std;

void test(const Sequence& uls)
{
    assert(uls.size() == 2);
    ItemType x = 999;
    assert(uls.get(0, x) && x == 20);
    assert(uls.get(1, x) && x == 10);
}

int main()
{
    Sequence s;
    s.insert(0, 10);
    s.insert(0, 20);
    test(s);
    cout << "Passed all tests" << endl;
}

#else

#include <string>
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    cout << "none defined" << endl;
}

#endif

