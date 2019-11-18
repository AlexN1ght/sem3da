#include <algorithm>
#include <iostream>
#include "List.hpp"

template <class K, class V>
class TKeyNode;
template <class K, class V, int T>
class TNode;
template <class K, class V, int T>
class TBTree;

template <class K, class V, int T>
class TKeyVal {
    using node_ptr = std::shared_ptr<TNode<K,V,T>>;
    public:
        TKeyVal() {
            key = 999;
            left = nullptr;
        }
        TKeyVal(node_ptr to) {
            key = 999;
            left = to;
        }
        TKeyVal(K keyIn, V valIn): key(keyIn), value(valIn) {
            left = nullptr;
        }

        friend std::ostream& operator<< (std::ostream &out, const TKeyVal<K,V,T> &kv) {
            out << '(' << "key: " << kv.key << " value: " << kv.value << ") ";
            return out;
        }
        K key;
        V value;
        node_ptr left; 
};

template <class K, class V, int T>
class TNode {
    public:
        using node_ptr = std::shared_ptr<TNode<K,V,T>>;
        using list_node_ptr = std::shared_ptr<TLNode<TKeyVal<K,V,T>>>;

        TNode(node_ptr from) {
            prev = from;
            keys.Insert(0, TKeyVal<K,V,T>());
        }
        TNode(node_ptr from, node_ptr to) {
            prev = from;
            keys.Insert(0, TKeyVal<K,V,T>(to));
        }
        TNode(list_node_ptr st, list_node_ptr en, node_ptr from) {
            prev = from;
            keys.NHead(st);
            keys.NTail(en);
            keys.ReSize();
        }
        int add (K& key, V& val){
            if (keys.Size() == 2 * T) {
                if (prev == nullptr) {
                    prev = std::make_shared<TNode<K,V,T>>(TNode<K,V,T>(nullptr, std::make_shared<TNode<K,V,T>>(*this)));
                    prev->Print();
                }
                list_node_ptr mid = std::make_shared<TLNode<TKeyVal<K,V,T>>>(TLNode<TKeyVal<K,V,T>>(keys.Get(T-1)));
                std::cout << mid->next << '\n';
                node_ptr left = std::make_shared<TNode<K,V,T>>(TNode<K,V,T>(keys.Get(0), keys.Get(T-1), prev));
                std::cout << mid->next << '\n';
                keys.NHead(mid->next);
                std::cout << mid->next << '\n';
                keys.ReSize();
                mid->value.left = left;
                puts("JGKLJGLKJGLKGLKJGKJG");
                this->Print();
                prev->Print();
                prev->Plus(mid);
                prev->Print();
                keys.ReSize();
                if (key < mid->value.key)
                    return left->add(key, val);
                if (key > mid->value.key)
                    return this->add(key, val);
                else
                    return 0;
            }
            list_node_ptr tmp = keys.Get(0);
            int s = keys.Size();
            for (int i = 0; i < (s - 1) ; ++i) {
                if (tmp->value.key > key) {
                    if (tmp->value.left) {
                        return tmp->value.left->add(key, val);
                    }
                    else {
                        keys.Insert(i, TKeyVal<K,V,T>(key, val));
                        return 1;
                    }
                } else if (tmp->value.key == key) {
                    return 0;
                }
                tmp = tmp->next;
            }
            if (tmp->value.left) {
                return tmp->value.left->add(key, val);
            }
            else {
                keys.Insert(s - 1, TKeyVal<K,V,T>(key, val));                
                return 1;
            }
        }
        int Plus(list_node_ptr In) {
            list_node_ptr tmp = keys.Get(0);
            int s = keys.Size();
            if (tmp->value.key > In->value.key || s == 1) {
                keys.Insert(0, In->value);
                return 1;
            }
            puts("Ter sdes");
            for (int i = 0; i < (s - 2) ; ++i) {
                if (tmp->next->value.key > In->value.key || tmp->next->value.key == (int)NULL) {
                    In->next = tmp->next;
                    tmp->next = In;
                    ++(keys.size);
                    return 1;
                }
                tmp = tmp->next;
            }
            In->next = tmp->next;
            tmp->next = In;
            ++(keys.size);
            return 1;
        }
        void Print() {
            keys.Print();
            int s = keys.Size();
            list_node_ptr tmp = keys.Get(0);
            puts("AAAAA");
            for (int i = 0; i < s ; ++i) {
                if (tmp->value.left) {
                    puts("I sho?");
                    std::cout << tmp->value;
                    tmp->value.left->keys.Print();
                }
                tmp = tmp->next;
            }
        }
        
        TList <TKeyVal<K,V,T>> keys;
        node_ptr prev;
};

template <class K, class V, int T>
class TBTree {
    using node_ptr = std::shared_ptr<TNode<K,V,T>>;
    using list_node_ptr = std::shared_ptr<TLNode<TKeyVal<K,V,T>>>;
    public:
        node_ptr root;
        TBTree() {
            root = std::make_shared<TNode<K,V,T>>(TNode<K,V,T>(nullptr));
        }
        int add(K key, V val) {
            if (root->add(key, val)) {
                while (root->prev != nullptr) {
                    puts("rerererebe");
                    root = root->prev;
                }
                return 1;
            }
            return 0;
        }
        void Print() {
            root->Print();
        }
    private:
        //node_ptr root;
};


