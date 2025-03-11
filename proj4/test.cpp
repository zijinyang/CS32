#include <iostream>
#include <string>
#include "bstset.h"

using namespace std;

int main(){
    BSTSet<int> set;
    set.insert(5);
    set.insert(3);
    cout << set.find(3).getVal() << endl;
}