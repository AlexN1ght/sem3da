#include <iostream>
#include <sstream>
#include "AC.hpp"
#include <unordered_map>
#include <vector>
#include <string>
#include <list>

int main() {
    std::ios::sync_with_stdio(false);
    TTrie<unsigned long> patt;
    unsigned long tmpT;
    char ch;
    
    std::vector<unsigned long> tmpWord;
    std::string lbuff;
    std::getline(std::cin, lbuff);
    std::istringstream buffS(lbuff);
    while(1) {
        if (buffS >> tmpT) {
            tmpWord.push_back(tmpT);
        } else {
            buffS.clear();
            if (buffS >> ch) {
                if (ch == '?') {
                    patt.add(tmpWord.data(), tmpWord.size());
                    patt.shift += 1;
                    tmpWord.clear();
                } else {
                    std::cout << "what&!&!???";
                }
            } else {
                patt.add(tmpWord.data(), tmpWord.size());
                tmpWord.clear();
                break;
            }
        }
    }
    patt.link();

    int line = 0;
    int posInLine = 0;
    size_t pos = 0;
    std::unordered_map<int, std::pair<int, int>> ansMap;
    TTrie<unsigned long>::TACNode<unsigned long>* tmp = patt.root;
    std::unordered_map<size_t, int> ansBuff;
    std::pair<int, int> ansTmp;

    while (std::getline(std::cin, lbuff)) {
        std::istringstream buffS(lbuff);
        line++;
        posInLine = 0;
        while (1) {
            if (buffS >> tmpT) {
                pos++;
                posInLine++;
                ansMap[pos] = std::pair<int,int>(line, posInLine);

                if (ansBuff.find(pos - patt.shift) == ansBuff.end()) {
                    ansBuff.insert(std::pair<int, int>(pos - patt.shift, 1));
                } else {
                    ansBuff[pos - patt.shift]++;
                }
                if (ansBuff[pos - patt.shift] == patt.count + 1) {
                    if ((int)pos - patt.shift >= 0) {
                        ansTmp = ansMap[pos - patt.shift + 1];
                        std::cout << ansTmp.first << ", " << ansTmp.second << '\n';
                    }
                }

                while (1) {
                    if (tmp->next.find(tmpT) != tmp->next.end()) {
                        tmp = tmp->next[tmpT];
                        if (tmp->id > 0) {
                            for (int i = 0; i < tmp->shift.size(); i++) {
                                if (ansBuff.find(pos - tmp->size - tmp->shift[i]) == ansBuff.end()) {
                                    ansBuff.insert(std::pair<int, int>(pos - tmp->size - tmp->shift[i], 1));
                                } else {
                                    ansBuff[pos - tmp->size - tmp->shift[i]]++;
                                }
                                if (ansBuff[pos - tmp->size - tmp->shift[i]] == patt.count + 1) {
                                    if ((int)pos - tmp->size - tmp->shift[i] >= 0) {
                                        ansTmp = ansMap[pos - tmp->size - tmp->shift[i] + 1];
                                        std::cout << ansTmp.first << ", " << ansTmp.second << '\n';
                                    }
                                }
                            }
                        }
                        if (tmp->outputLink != nullptr) {
                            for (int i = 0; i < tmp->shift.size(); i++) {
                                if (ansBuff.find(pos - tmp->outputLink->size - tmp->outputLink->shift[i]) == ansBuff.end()) {
                                    ansBuff.insert(std::pair<int, int>(pos - tmp->size - tmp->shift[i], 1));
                                } else {
                                    ansBuff[pos - tmp->outputLink->size - tmp->outputLink->shift[i]]++;
                                }
                                if (ansBuff[pos - tmp->outputLink->size - tmp->outputLink->shift[i]] == patt.count + 1) {
                                    if ((int)pos - tmp->size - tmp->shift[i] >= 0) {
                                        ansTmp = ansMap[pos - tmp->size - tmp->shift[i] + 1];
                                        std::cout << ansTmp.first << ", " << ansTmp.second << '\n';
                                    }
                                }
                            }
                        }
                        break;
                    } else {
                        if (tmp == patt.root) {
                            break;
                        }
                        tmp = tmp->failLink;
                    }
                }
            } else {
                break;
            }

        }
    }

    //patt.print();
    return 0;
}
