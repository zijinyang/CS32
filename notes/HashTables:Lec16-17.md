# Hash Tables

Data type for quick lookups

## Structure

Array of linked lists

**Ex** : Student ID numbers

### Insertion

* Student ID inserted at index (a "bucket") with same number as first n digits of ID number
* a **collision** occurs when more than 1 item ends up in the same bucket
  * Want to keep collisions to a minimum

### Note

* Keys sometimes have patterns, elements end up in a lot of the same buckets
  * ID numbers have a check digit
* **load factor** average number of items in each bucket: $\frac{number of items}{number of buckets}$
  * tend to choose around 0.7
* if key is not int, can convert key into an int using a **hash function**
  * Use large prime as # of buckets to hash, avoids collisions

#### String Hash Function

Typical Format

```cpp
unsigned int h = 2166136261u //use unsigned int for u
for(char c: string s)
{
    h += c;
    h *= 16777619
}
return h;
```

Usage

```cpp
#include <functional>
using namespace std;

string s = "hello";

unsigned int x = std::hash<string>()(s) % numberOfBuckets; //overloaded function call operator
```

## Hash Functions

* produce uniformly distributed values
* cheap
* deterministic

## Time Complexity

For a hash table with a constant number of buckets, operations are O(N)

* still very good for small n, better than logN

To make it faster, assume maximum load factor

* when maximum load factor exceeded, rehash the table by doubling the number of buckets
  * lookups become constant time in general
  * rehashing takes time, but doesn't occur much

## Incremental Rehashing

Rehash a constant number of items from old table every time a new item is inserted

* lookup needs to look in two tables, but still constant
* no extremely expensive rehashing step
  * upper bound for time complexity

## Maps (STL)

Implemented using BST

```cpp
#include <map>
maps<string, double> ious; // key type requires < operator
while(cin >> name >> amt)
  ious[name] += amt;
for(map<string, double>::iterator p = ious.begin(); p != ious.end(); p++) //always visits all pairs in increasing order of key
  cout << p->first << endl;

// ious
// ===
// fred ==> 13 
// ethel ==> 5
```

## Unordered Sets

Implemented using hash table

```cpp
#include <unordered_set>

unordered_set<int> s;
s.insert(10);
s.insert(30);
s.insert(10);
cout << s.size(); //2
if (s.find(20 == s.end()))
  cout << "20 is not in the set";
for(unordered_set<int>::iterator p = s.begin(); != s.end(); p++)
  cout << *p << endl;
s.erase(30);
```
