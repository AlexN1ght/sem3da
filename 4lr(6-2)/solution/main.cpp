#include <iostream>
#include <sstream>
#include "AC.hpp"
#include <vector>
#include <string>

int main() {
    std::ios::sync_with_stdio(false);
    TTrie<unsigned long long> patt;
    unsigned long long tmpValue;
    char ch;
    
    std::vector<unsigned long long> tmpWord;
    std::string lbuff;
    std::getline(std::cin, lbuff);
    std::istringstream buffS(lbuff);

    while (true) {
        if (buffS >> tmpValue) {
            tmpWord.push_back(tmpValue);
        } else {
            buffS.clear();
            if (buffS >> ch) {
                if (ch == '?') {
                    patt.add(tmpWord.data(), tmpWord.size());
                    patt.addJoker();
                    tmpWord.clear();
                }
            } else {
                patt.add(tmpWord.data(), tmpWord.size());
                tmpWord.clear();
                break;
            }
        }
    }
    patt.link();

    size_t line = 0;
    size_t posInLine = 0;
    size_t pos = 0;
    std::vector<std::pair<size_t, size_t>> ansMap;
    TTrie<unsigned long long>::TACNode<unsigned long long>* tmp = patt.root;
    std::vector<size_t> ansBuff;
    std::pair<size_t, size_t> ansTmp;

    while (std::getline(std::cin, lbuff)) {
        std::istringstream buffS(lbuff);
        line++;
        posInLine = 0;
        while (true) {
            if (buffS >> tmpValue) {
                ansBuff.push_back(0);
                pos++;
                posInLine++;
                ansMap.push_back(std::pair<int,int>(line, posInLine));

                if (((long)pos - (long)patt.Size()) >= 0) {
                    ansBuff[pos - patt.Size()]++;
                    if (ansBuff[pos - patt.Size()] == patt.Count() + 1 && patt.Size() != 0) {
                        ansTmp = ansMap[pos - patt.Size()];
                        std::cout << ansTmp.first << ", " << ansTmp.second << '\n';
                    }
                }

                while (true) {
                    if (tmp->next.find(tmpValue) != tmp->next.end()) {
                        tmp = tmp->next[tmpValue];
                        if (tmp->id > 0) {
                            for (size_t i = 0; i < tmp->shift.size(); i++) {
                                if (((long)pos - (long)tmp->size - (long)tmp->shift[i]) >= 0) {
                                    ansBuff[pos - tmp->size - tmp->shift[i]]++;
                                    if (ansBuff[pos - tmp->size - tmp->shift[i]] == patt.Count() + 1 && patt.Size() != 0) {
                                        ansTmp = ansMap[pos - tmp->size - tmp->shift[i]];
                                        std::cout << ansTmp.first << ", " << ansTmp.second << '\n';
                                    }
                                }
                            }
                        }
                        if (tmp->outputLink != nullptr) {
                            for (size_t i = 0; i < tmp->outputLink->shift.size(); i++) {
                                if (((long)pos - (long)tmp->outputLink->size - (long)tmp->outputLink->shift[i]) >= 0) {
                                    ansBuff[pos - tmp->outputLink->size - tmp->outputLink->shift[i]]++;
                                    if (ansBuff[pos - tmp->outputLink->size - tmp->outputLink->shift[i]] == patt.Count() + 1 &&
                                            patt.Size() != 0) {
                                        ansTmp = ansMap[pos - tmp->outputLink->size - tmp->outputLink->shift[i]];
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
