#include <iostream>
#include "Vector.hpp"

struct keyVal {
	char key[33];
	char value[65];
};

int atoi(char a) {
    if (a >= 'a') {
        return a -'a' + 10;
    }
    return a - '0';
}

void countingSortInDig(TVector <keyVal>& unsorted, const int dig) {
    int count[16]{0};
    TVector <keyVal> out(unsorted.size());
    for (int i = 0; i <  unsorted.size(); i++) {
	    count[atoi(unsorted[i].key[dig])]++;
	}
	for (int i = 1; i < 16; i++) {
	    count[i] = count[i] + count[i - 1];
	}
	for (int i = unsorted.size() - 1; i >= 0; i--) {
	    out[--count[atoi(unsorted[i].key[dig])]] = unsorted[i];
	}
	swap(out, unsorted);
}

void radixSort(TVector<keyVal>& unsorted) {
    for (int i = 3; i >= 0; i--) {
        countingSortInDig(unsorted, i);
    }
}

int main(void) {
	 TVector <keyVal> entries;
	 keyVal tmp;
	 while(std::cin >> tmp.key >> tmp.value) {
	    entries.push_back(tmp);
	 }
	 radixSort(entries);
	 for (int i = 0; i <  entries.size(); i++) {
	    std::cout << entries[i].key << '\t' << entries[i].value << std::endl;
	 }
	 return 0;
}
