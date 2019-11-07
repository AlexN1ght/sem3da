#include <iostream>
#include <string>
#include "List.hpp"


int main() {
    TList<std::string> test;
    std::cout << test.Insert(0, "69q") << std::endl;
    std::cout << test.Insert(1, "2w") << std::endl;
    test.Print();
    std::cout << test.Insert(3, "9e") << std::endl; 
    std::cout << test.Insert(2, "3r") << std::endl; 
    std::cout << test.Insert(3, "4e") << std::endl; 
    std::cout << test.Size() << std::endl; 
    test.Print();
    TList<std::string> test2(test.Get(1), test.Get(4));
    test2.Print();
    std::cout << test2.Size() << std::endl;
    return 0;
}