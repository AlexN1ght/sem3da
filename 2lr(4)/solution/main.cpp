
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
            std::fill(stor, stor + 257, '\0');
        }
        TString(const TString& In){
            std::copy(In.stor, In.stor + 257, stor);
        }

        TString operator= (const TString& In) {
            std::copy(In.stor, In.stor + 257, stor);
            return *this;
        }

        friend std::ostream& operator<< (std::ostream &out, const TString& stO) {
            out << stO.stor;
            return out;
        }

        friend std::istream& operator>> (std::istream &is, TString& stI)  {
            /*
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
            */
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
            int i = 0;
            for (; stor[i] != '\0' && In.stor[i] != '\0'; ++i) {
                if (stor[i] != In.stor[i]) {
                    if (stor[i] < In.stor[i]) {
                        return true;
                    } else {
                        return false;
                    }
                }
            }
            if ((stor[i] == '\0') && (In.stor[i] != '\0')){
                return true;
            } else {
                return false;
            }
        }

        bool operator <= (const TString& In) {
            int i = 0;
            for (; stor[i] != '\0' && In.stor[i] != '\0'; ++i) {
                if (stor[i] != In.stor[i]) {
                    if (stor[i] <= In.stor[i]) {
                        return true;
                    } else {
                        return false;
                    }
                }
            }
            if ((stor[i] == '\0' && In.stor[i] == '\0') || (stor[i] == '\0' && In.stor[i] != '\0')) {
                return true;
            } else {
                return false;
            }
        }

        bool operator > (const TString& In) {
            int i = 0;
            for (; stor[i] != '\0' && In.stor[i] != '\0'; ++i) {
                if (stor[i] != In.stor[i]) {
                    if (stor[i] > In.stor[i]) {
                        return true;
                    } else {
                        return false;
                    }
                }
            }
            if ((stor[i] != '\0') && (In.stor[i] == '\0')) {
                return true;
            } else {
                return false;
            }
        }
        bool operator>= (const TString& In) {
            int i = 0;
            for (; stor[i] != '\0' && In.stor[i] != '\0'; ++i) {
                if (stor[i] != In.stor[i]) {
                    if (stor[i] >= In.stor[i]) {
                        return true;
                    } else {
                        return false;
                    }
                }
            }
            if ((stor[i] == '\0' && In.stor[i] == '\0') || (stor[i] != '\0' && In.stor[i] == '\0'))  {
                return true;
            } else {
                return false;
            }
        }
        bool operator== (const TString& In) {
            int i = 0;
            for (; stor[i] != '\0' && In.stor[i] != '\0'; ++i) {
                if (stor[i] != In.stor[i]) {
                    return false;
                }
            }
            if (stor[i] != In.stor[i]) {
                return false;
            }
            return true;
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
    return 0;
}
