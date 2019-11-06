#include <iostream>
#include "Vector.hpp"

const int MD5_LENGTH = 32;

struct keyVal {
    char key[33];
    char value[65];
};

int Atoi(char a) {
    if (a >= 'a') {
        return a -'a' + 10;
    }
    return a - '0';
}



void CountingSortInDig(TVector <keyVal>& unsorted, const int dig) {
   int count[16]{0};
   TVector <keyVal> out(unsorted.Size());
   for (int i = 0; i <  unsorted.Size(); i++) {
        count[Atoi(unsorted[i].key[dig])]++;
    }
    for (int i = 1; i < 16; i++) {
        count[i] = count[i] + count[i - 1];
    }
    for (int i = unsorted.Size() - 1; i >= 0; i--) {
        out[--count[Atoi(unsorted[i].key[dig])]] = unsorted[i];
    }
    Swap(out, unsorted);
}

void RadixSort(TVector<keyVal>& unsorted) {
    for (int i = MD5_LENGTH - 1; i >= 0; i--) {
        CountingSortInDig(unsorted, i);
    }
}

int main(void) {
    std::ios::sync_with_stdio(false);
    TVector <keyVal> entries;
    keyVal tmp;
    while(std::cin >> tmp.key >> tmp.value) {
        entries.Push_back(tmp);
    }
    RadixSort(entries);
    for (int i = 0; i <  entries.Size(); i++) {
        std::cout << entries[i].key << '\t' << entries[i].value << std::endl;
    }
    return 0;
}

