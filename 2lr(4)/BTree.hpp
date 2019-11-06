#include<algotithm>
#include<

class TKeyNode;
class TNode;
class TBTree;


class TKeyVal {
    public:
        TKeyVal() {
            std::fill(key, key + 256, 'z');
        }
        TKeyVal(char* keyIn, unsigned long long valIn) {
            int i = 0;
            while (keyIn[i] != '\0') {
                key[i] = keyIn[i];
                i++;
            }
            key[i] = '\0';
        }
    private:
        char key [257];
        unsigned long long value;
        TNode* next; 
}

template <class K, class V>
class TNode {
    public:
        TNode() {
            keys.push_back(TKeyVal());
        }
    private:
        TList <TKeyVal> keys;
        Node* prev;
}

class TBTree {
    public:
        TBTree() {
             root = new TNode();
        }
    private:
        TNode* root;
}


