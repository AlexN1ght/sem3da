
#include <iostream>
#include <string>
#include <cstring>
#include "Vector.hpp"
#include "BTree.hpp"

bool is_space(char c) {
    return (c == '\n' || c == ' ' || c == '\t' || c == EOF) ? true : false;
}

char to_lo(char c) {
    if (c >= 'A' && c <= 'Z') {
        return c + 'a' - 'A';
    }
    return c;
}

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
            is.sync();
            int i = 0;
            while(is_space((char)is.peek())) {
                if(is.get() == EOF) {
                    return is;
                }
            }
            while(!is_space((char)is.peek())) {
                stI.stor[i] = (char)to_lo(is.get());
                i++;
            }
            stI.stor[i] = '\0';
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
                //std::cout << "OK\n";
                puts("OK");
            } else {
                //std::cout << "Exist\n";
                puts("Exist");
            }
        } else if (command[0] == '-') {
            std::cin >> key;
            if(tree.del(key)) {
                //std::cout << "OK\n";
                puts("OK");
            } else {
                //std::cout << "NoSuchWord\n";
                puts("NoSuchWord");
            }
        } else if (command[0] == '!') {
            std::cin >> command >> key;
            if (command[0] == 's') {
                if(tree.Save(key.CStr())) {
                    //std::cout << "OK\n";
                    puts("OK");
                } else {
                    //std::cout << "ERROR:\n";
                    puts("ERROR");
                }
            } else if (command[0] == 'l') {
                if(tree.Load(key.CStr())) {
                    //std::cout << "OK\n";
                    puts("OK");
                } else {
                    //std::cout << "ERROR:\n";
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
                //std::cout << "OK: " << val << '\n';
            } catch (int) {
                //std::cout << "NoSuchWord\n";
                puts("NoSuchWord");
            }
        }
    }
    printf("cons: %d\ncop: %d\nmov: %d\nKcons: %d\nKcop: %d\nKmov: %d\n", cons, cop, mov, Kcons, Kcop, Kmov);
    return 0;
}
