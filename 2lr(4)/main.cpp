#include <iostream>
#include <string>
#include "BTree.hpp"


int main() {
    TBTree<int, int, 3> test;
    puts("Start");
    test.add(1,4);
    test.add(2,9);
    test.add(-4,1);
    test.add(0,9);
    test.add(3,9);
    test.Print();
    test.add(18,9);
    puts("LCP");
    test.Print();
    test.add(14,-69);
    test.Print();
    
    return 0;
}