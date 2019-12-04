
#include <iostream>
#include <string>
#include <cstring>
#include "Vector.hpp"
#include "BTree.hpp"


class TString {
    public:
        TString(){
            cons++;
            std::fill(stor, stor + 257, '\0');
        }
        TString(const TString& In){
            cop++;
            std::copy(In.stor, In.stor + 257, stor);
        }
        TString(TString&& In){
            mov++;
            std::swap(In.stor, stor);
        }

        TString& operator= (const TString& In) {
            cop++;
            std::copy(In.stor, In.stor + 257, stor);
            return *this;
        }

        friend std::ostream& operator<< (std::ostream &out, const TString& stO) {
            out << stO.stor;
            return out;
        }

        friend std::istream& operator>> (std::istream &is, TString& stI)  {
            std::cin >> stI.stor;
            for(int i = 0; stI.stor[i] != '\0'; ++i) {
                stI.stor[i] = (char)tolower(stI.stor[i]);
            }
            return is;
        }

        bool operator < (const TString& In) {
            return strcmp(stor, In.stor) < 0 ? 1 : 0;
        }

        bool operator <= (const TString& In) {
            return strcmp(stor, In.stor) <= 0 ? 1 : 0;
        }

        bool operator > (const TString& In) {
            return strcmp(stor, In.stor) > 0 ? 1 : 0;
        }
        bool operator>= (const TString& In) {
            return strcmp(stor, In.stor) >= 0 ? 1 : 0;
        }
        bool operator== (const TString& In) {
            return strcmp(stor, In.stor) == 0 ? 1 : 0;
        }

        char operator[] (int n) {
            if (n < 0 || n > 257) {
                throw std::out_of_range("You are doing this wrong!");
            }
            return stor[n];
        }
        char* CStr() {
            return stor;
        }
        ~TString() {
            //delete[] stor;
        }

    private:
        
        char stor[257];
};

int main() {
    std::ios::sync_with_stdio(false);
    using String = TString;
    TBTree<String, unsigned long long, 10> tree;
    String command;
    String key;
    unsigned long long val;

    while(std::cin >> command) {
        if (command[0] == '+') {
            std::cin >> key >> val;
            if(tree.add(key,val)) {
                puts("OK");
            } else {
                puts("Exist");
            }
        } else if (command[0] == '-') {
            std::cin >> key;
            if(tree.del(key)) {
                puts("OK");
            } else {
                puts("NoSuchWord");
            }
        } else if (command[0] == '!') {
            std::cin >> command >> key;
            if (command[0] == 's') {
                if(tree.Save(key.CStr())) {
                    puts("OK");
                } else {
                    puts("ERROR");
                }
            } else if (command[0] == 'l') {
                if(tree.Load(key.CStr())) {
                    puts("OK");
                } else {
                    puts("ERROR");
                }
            }
        /*
        } else if (command[0] == 'p') {
            tree.Print();
        */
        } else {
            try {
                val = tree.Find(command);
                printf("OK: %llu\n", val);
            } catch (int) {
                puts("NoSuchWord");
            }
        }
    }
    return 0;
}
