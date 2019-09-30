#include <iostream>
#include <time.h>
#include <sys/time.h>
#include "Vector.hpp"

const int MD5_LENGTH = 32;

char Itoa(int a) {
    if (a < 10) {
        return a + '0';
    } else {
        return a + 'a' - 10;
    }
}

void KGen(char* out)
{
    for(int i = 0; i < 32; i++) {
        out[i] = Itoa((rand() % 16)) ;
    }
}

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
     srand(time(NULL));
     std::ios::sync_with_stdio(false);
	 keyVal tmp;
	 int N;
	 while(true) {
	 TVector <keyVal>* entries = new TVector <keyVal>;
	 std::cin >> N;
	 tmp.value[0] = 'f';
	 tmp.value[1] = '\0';
	 for(int i = 0; i < N; i++) {
	    KGen(tmp.key);
	    entries->Push_back(tmp);
	 }
	 struct timeval stop, start;
	 gettimeofday(&start, NULL);
     RadixSort(*entries);
     gettimeofday(&stop, NULL);
     long timeDiff = (long)((stop.tv_sec - start.tv_sec) * 1000.0f + (stop.tv_usec - start.tv_usec) / 1000.0f);
	 //for (int i = 0; i <  entries.Size(); i++) {
	  //  std::cout << entries[i].key << '\t' << entries[i].value << std::endl;
	 //}
	 std::cout << timeDiff << std::endl;
	 delete entries;
	 }
	 return 0;
}
