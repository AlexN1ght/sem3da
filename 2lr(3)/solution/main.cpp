#include "Patricia.hpp"
#include <iostream>

void tolow(char* a) {
    for (int i = 0; a[i] != '\0'; i++) {
        if (a[i] >= 'A' && a[i] <= 'Z') {
            a[i] = tolower(a[i]);
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    char comm[50];
    char key[257]{'\0'};
    unsigned long long value;

    TPatricaia stor;

    while(std::cin >> comm) {
        if (comm[0] == '+') {
            std::cin >> key >> value;
            tolow(key);
            if(stor.Add(key,value)) {
                puts("OK");
            } else {
                puts("Exist");
            }
        } else if (comm[0] == '-') {
            std::cin >> key;
            tolow(key);
            if(stor.Del(key)) {
                puts("OK");
            } else {
                puts("NoSuchWord");
            }
        } else if (comm[0] == '!') {
            std::cin >> comm >> key;
            if (comm[0] == 'S') {
                if(stor.Save(key)) {
                    puts("OK");
                } else {
                    puts("ERROR");
                }
            } else if (comm[0] == 'L') {
                if(stor.Load(key)) {
                    puts("OK");
                } else {
                    puts("ERROR");
                }
            }
        } else {
            try {
                tolow(comm);
                value = stor.Find(comm);
                printf("OK: %llu\n", value);
            } catch (...) {
                puts("NoSuchWord");
            }
        }
    }
    return 0;
}
