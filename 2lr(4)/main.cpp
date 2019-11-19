#include <iostream>
#include <string>
#include "BTree.hpp"


int main() {
    TBTree<std::string, int, 3> test;
    test.add("1",4);
    test.add("2",9);
    test.add("3",1);
    test.add("4",9);
    test.add("7",9);
    puts("");
    test.Print();
    test.add("8",9);
    puts("");
    test.Print();
    test.add("6",-69);
    test.add("5",-69);
    puts("");
    test.Print();
    
    return 0;
}