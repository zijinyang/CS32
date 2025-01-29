        #include "Sequence.h"
        #include <string>
        #include <iostream>
        #include <cassert>
        using namespace std;

        void test()
        {
            Sequence ss;
            assert(ss.insert(0, "lavash") == 0);
            assert(ss.insert(0, "tortilla") == 0);
            assert(ss.size() == 2);
            ItemType x = "injera";
            assert(ss.get(0, x)  &&  x == "tortilla");
            assert(ss.get(1, x)  &&  x == "lavash");
        }

        int main()
        {
            test();
            cout << "Passed all tests" << endl;
        }