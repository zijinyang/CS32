#include "bstset.h"
#include "fm.h" // Assuming FlightManager is defined in this header
#include "tp.h"
#include <iostream>
#include <cassert>
#include <vector>

using namespace std;

void testGetAndAdvance()
{
    BSTSet<int> set;
    set.insert(10);
    set.insert(5);
    set.insert(15);
    set.insert(12);

    BSTSet<int>::SetIterator it = set.find(10);
    cout << "gets here" << endl;

    assert(*it.get_and_advance() == 10);
    assert(*it.get_and_advance() == 12);
    assert(*it.get_and_advance() == 15);
    assert(it.get_and_advance() == nullptr); // No more elements to advance to

    std::cout << "testGetAndAdvance passed!" << std::endl;
}

void testFlightManager()
{
    FlightManager manager;

    // Test adding flights
    manager.load_flight_data("/Users/kevinyang/Documents/CS32/proj4/all_flights.txt");
    long end_time = 2036320800;
    vector<FlightSegment> v = manager.find_flights("HHR", 1736285400, 1736285400 + 1); 
    for(auto& f : v)
    {
        cout << f.destination_airport << endl;
    }
}

void testBSTSetInsertAndFind()
{
    BSTSet<int> set;
    set.insert(10);
    set.insert(5);
    set.insert(15);
    set.insert(12);

    assert(set.find(10).get_and_advance() != nullptr);
    assert(*set.find(10).get_and_advance() == 10);
    assert(set.find(20).get_and_advance() == nullptr); // Element not in set

    std::cout << "testBSTSetInsertAndFind passed!" << std::endl;
}

void testBSTSetFindFirstNotSmaller()
{
    BSTSet<int> set;
    set.insert(10);
    set.insert(5);
    set.insert(15);
    set.insert(12);

    assert(set.find_first_not_smaller(6).get_and_advance() != nullptr);
    assert(*set.find_first_not_smaller(6).get_and_advance() == 10);
    assert(set.find_first_not_smaller(16).get_and_advance() == nullptr); // No element not smaller

    std::cout << "testBSTSetFindFirstNotSmaller passed!" << std::endl;
}

void testBSTSetGetAndAdvance()
{
    BSTSet<int> set;
    set.insert(10);
    set.insert(5);
    set.insert(15);
    set.insert(12);

    BSTSet<int>::SetIterator it = set.find(5);
    assert(*it.get_and_advance() == 5);
    assert(*it.get_and_advance() == 10);
    assert(*it.get_and_advance() == 12);
    assert(*it.get_and_advance() == 15);
    assert(it.get_and_advance() == nullptr); // No more elements to advance to

    std::cout << "testBSTSetGetAndAdvance passed!" << std::endl;
}

int main()
{
    // testInsertAndFind();
    // testFindFirstNotSmaller();
    // testGetAndAdvance();
    testFlightManager();
    testBSTSetInsertAndFind();
    testBSTSetFindFirstNotSmaller();
    testBSTSetGetAndAdvance();

    std::cout << "All tests passed!" << std::endl;
    return 0;
}