
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
        TString(): size(1){
            stor = new char[size];
            stor[0] = '\0';
        }
        TString(const TString& In): size(In.size){
            //puts("Test1");
            stor = new char[size];
            std::copy(In.stor, In.stor + size, stor);
            //puts("Test2");
        }

        TString operator= (const TString& In) {
            size = In.size;
            //puts("Test");
            delete[] stor;
            stor = new char[size];
            std::copy(In.stor, In.stor + size, stor);
            return *this;
        }

        friend std::ostream& operator<< (std::ostream &out, const TString& stO) {
            for (int i = 0; stO.stor[i] != '\0'; i++) {
                out << stO.stor[i];
            }
            return out;
        }

        friend std::istream& operator>> (std::istream &is, TString& stI)  {
            is.sync();
            TVector<char> temp;
            while(is_space((char)is.peek())) {
                if(is.get() == EOF) {
                    return is;
                }
            }
            while(!is_space((char)is.peek())) {
                temp.Push_back(to_lo(is.get()));
            }
            temp.Push_back('\0');
            delete[] stI.stor;
            stI.size = temp.Size(); 
            stI.stor = new char[stI.size];
            std::copy(temp.Begin(), temp.End(), stI.stor);
            return is;
        }

        bool operator < (const TString& In) {
            for (int i = 0; (i < size - 1) && (i < In.size - 1); ++i) {
                if (stor[i] != In.stor[i]) {
                    if (stor[i] < In.stor[i]) {
                        return true;
                    } else {
                        return false;
                    }
                }
            }
            if (size < In.size) {
                return true;
            } else {
                return false;
            }
        }

        bool operator <= (const TString& In) {
            for (int i = 0; (i < size - 1) && (i < In.size - 1); ++i) {
                if (stor[i] != In.stor[i]) {
                    if (stor[i] <= In.stor[i]) {
                        return true;
                    } else {
                        return false;
                    }
                }
            }
            if (size <= In.size) {
                return true;
            } else {
                return false;
            }
        }

        bool operator > (const TString& In) {
            for (int i = 0; (i < size - 1) && (i < In.size - 1); ++i) {
                if (stor[i] != In.stor[i]) {
                    if (stor[i] > In.stor[i]) {
                        return true;
                    } else {
                        return false;
                    }
                }
            }
            if (size > In.size) {
                return true;
            } else {
                return false;
            }
        }
        bool operator>= (const TString& In) {
            for (int i = 0; (i < size - 1) && (i < In.size - 1); ++i) {
                if (stor[i] != In.stor[i]) {
                    if (stor[i] >= In.stor[i]) {
                        return true;
                    } else {
                        return false;
                    }
                }
            }
            if (size >= In.size) {
                return true;
            } else {
                return false;
            }
        }
        bool operator== (const TString& In) {
            if (size != In.size) {
                return false;
            }
            for (int i = 0; i < size - 1; ++i) {
                if (stor[i] != In.stor[i]) {
                        return false;
                }
            }
            return true;
        }

        char operator[] (int n) {
            if (n < 0 || n > size) {
                throw std::out_of_range("You are doing this wrong!");
            }
            return stor[n];
        }
        ~TString() {
            delete[] stor;
        }

    private:
        
        char* stor;
        int size;
};

int main() {
    using String = TString;
    TBTree<String, unsigned long long, 3> tree;
    String command;
    String key;
    unsigned long long val;

    while(std::cin >> command) {
        if (command[0] == '+') {
            std::cin >> key >> val;
            if(tree.add(key,val)) {
                std::cout << "OK\n";
            } else {
                std::cout << "Exist\n";
            }
        } else if (command[0] == '-') {
            std::cin >> key;
            if(tree.del(key)) {
                std::cout << "OK\n";
            } else {
                std::cout << "NoSuchWord\n";
            }
        } else if (command[0] == 'p') {
            tree.Print();
        } else {
            try {
                val = tree.Find(command);
                std::cout << "OK: " << val << '\n';
            } catch (int) {
                std::cout << "NoSuchWord\n";
            }
        }
    }
    return 0;
}
