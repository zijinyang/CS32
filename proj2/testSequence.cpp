// #include "Sequence.h"
// #include <iostream>
// #include <cassert>
// using namespace std;

// void initTests(){
//     Sequence s;
//     assert(s.empty());
//     ItemType x = 97;
//     assert(!s.get(68, x)  &&  x == 97); // x unchanged by get failure
//     assert(s.find(42) == -1);
//     assert(s.insert(42) == 0);
//     assert(s.size() == 1  &&  s.find(42) == 0);
//     assert(s.get(0, x)  &&  x == 42);
//     assert(s.erase(0) && s.empty());
//     assert(s.get(0,x) == false);
// }

// void testCopy(){
//     Sequence s;
//     assert(s.insert(42) == 0);
//     assert(s.insert(5) == 0);

//     ItemType x; 
//     Sequence s1(s);
//     assert(s1.get(0,x) && x == 5);

//     Sequence s3;
//     Sequence s4(s3);
//     assert(s4.empty());
//     assert(s4.get(0,x) == false);
// }

// void testAssignment(){
//     Sequence s;
//     assert(s.insert(42) == 0);
//     assert(s.insert(5) == 0);

//     ItemType x;
//     Sequence s2;
//     s2 = s;
//     assert(s2.get(0,x) && x == 5);

//     Sequence s3;
//     s = s3;
//     assert(s.empty());
//     assert(s.get(0,x) == false);
// }

// void testSwap(){
//     Sequence s1;
//     assert(s1.insert(0,5) == 0); // 5

//     Sequence s2;
//     s1.swap(s2); //s1:5 s2:empty
//     assert(s1.size() == 0);
//     assert(s2.find(5) == 0);
//     assert(s2.set(0,2) == true); // s1: 2
//     assert(s2.find(2) == 0);
//     ItemType x;
//     assert(s2.get(0,x) == true);
//     assert(x == 2);

//     Sequence s3 = s2;
//     assert(s1.insert(1) == 0);
//     assert(s1.insert(2) == 1);

//     s1.swap(s3);
    
//     assert(s1.size() == 1);
// }

// void testInsert(){
//     Sequence s;
//     s.insert(0,1);
//     s.insert(2);
//     s.insert(6);
//     ItemType x;
//     s.get(0,x);
//     assert(x == 1);
//     assert(s.insert(5) == 2);
//     assert(s.size() == 4);
// }

// void testRemove(){
//     Sequence s;
//     s.insert(1);
//     s.insert(1);
//     s.insert(2);
//     s.insert(2);
//     s.insert(2);
//     s.insert(6);

//     assert(s.remove(2) == 3);
//     assert(s.remove(6) == 1);
//     assert(s.insert(1,5) == 1);
//     assert(s.remove(1) == 2);
//     assert(s.remove(5));
//     assert(s.remove(25) == 0);
//     assert(s.empty());
// }

// void testSubsequence1()
// {
//     Sequence s1;
//     Sequence s2;

//     int arr[] {1,3,5,7,9};
//     for(int i = 0; i < 5; i++){
//         s1.insert(arr[i]);
//     }

//     for(int i = 1; i < 4; i++){
//         s2.insert(arr[i]);
//     }
//     assert(subsequence(s1,s2) == 1);
    
//     Sequence s3;
//     assert(subsequence(s1,s3) == -1);

// }

// void testSubsequence2()
// {
//     Sequence s1;
//     Sequence s2;
//     int arr[] {1,3,1,3};
//     for(int i = 0; i < 4; i++){
//         s1.insert(i,arr[i]);
//     }
//     for(int i = 0; i < 2; i++){
//         s2.insert(i,arr[i]);
//     }
//     assert(subsequence(s1, s2) == 0);    
//     s2.remove(1);
//     assert(subsequence(s1, s2) == 1);
// }

// void testZipper(){
//     Sequence s1;
//     Sequence s2;
//     int arr[] {1,3,5,7,9};
//     for(int i = 0; i < 5; i++){
//         s1.insert(arr[i]);
//     }

//     for(int i = 1; i < 4; i++){
//         s2.insert(arr[i]);
//     }

//     Sequence s3;

//     zipper(s1,s2,s3);
//     s3.dump();

//     // zipper(s1,s2,s1);
//     // s1.dump();
    
//     Sequence s4;
//     zipper(s1,s4,s3);
//     s3.dump();
// }

// void testZipper2(){
//     Sequence s1;
//     Sequence s2;
//     int arr[] {1,3,5,7,9};
//     for(int i = 0; i < 5; i++){
//         s1.insert(arr[i]);
//     }

//     for(int i = 1; i < 4; i++){
//         s2.insert(arr[i]);
//     }

//     Sequence result;
//     zipper(s2,s1,result);
//     result.dump();
// }

// int main()
// {
//     initTests();
//     testAssignment();
//     testCopy();
//     testSwap();
//     testInsert();
//     testRemove();
//     testSubsequence1();
//     testSubsequence2();
//     // testZipper();
//     // testZipper2();
//     cout << "Passed all tests" << endl;
// }