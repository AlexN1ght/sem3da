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
    test.add("8",9);
    test.add("11",-69);
    test.add("12",-69);
    test.add("124",-69);
    test.add("6",-69);
    test.add("5",-69);
    test.add("5",-69);
    test.add("22",-69);
    test.add("23",-69);
    test.add("24",-69);
    test.add("r",-69);
    test.add("ffwef",-69);
    test.add("ool",-69);
    test.add("z",-69);
    test.add("8ol",-69);
    test.add("ool",-69);
    test.add("owl",-69);
    test.add("qq",-69);
    test.add("qqq",-69);
    test.add("333",-69);
    puts("");
    test.Print();
    test.del("1");
    test.Print();
    test.del("2");
    test.Print();
    
    return 0;
}