#include <iostream>
#include "AC.hpp"

int main() {
    TTrie<char> test;
    test.add("potato");
    test.add("theater");
    test.add("tattoo");
    test.add("t");
    test.add("other");
    test.link();
    test.print(0);
    return 0;
}
