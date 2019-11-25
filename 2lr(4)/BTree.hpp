#include <algorithm>
#include <iostream>
#include "List.hpp"

template <class K, class V, int T>
class TNode;
template <class K, class V, int T>
class TBTree;

template <class K, class V, int T>
class TKeyVal {
    using node_ptr = TNode<K,V,T>*;
    public:
        TKeyVal() {
            left = nullptr;
        }
        TKeyVal(node_ptr to) {
            left = to;
        }
        TKeyVal(K keyIn, V valIn): key(keyIn), value(valIn) {
            left = nullptr;
        }
        TKeyVal(K keyIn, V valIn, node_ptr to): key(keyIn), value(valIn) {
            left = to;
        }

        friend std::ostream& operator<< (std::ostream &out, const TKeyVal<K,V,T> &kv) {
            out << kv.key << " :: " << kv.value << " ";
            return out;
        }
        K key;
        V value;
        node_ptr left; 
};

template <class K, class V, int T>
TLNode<TKeyVal<K,V,T>>* findKey(TList <TKeyVal<K,V,T>>& keys, K& key) {
    TLNode<TKeyVal<K,V,T>>* tmp = keys.Get(0);
    int s = keys.Size();
    for (int i = 0; i < (s - 1) ; ++i) {
        if (tmp->value.key >= key) {
            return tmp;
        } 
        tmp = tmp->next;
    }
    return tmp;
}
template <class K, class V, int T>
TLNode<TKeyVal<K,V,T>>* findPrevKey(TList <TKeyVal<K,V,T>>& keys, K& key) {
    TLNode<TKeyVal<K,V,T>>* tmp = keys.Get(0);
    int s = keys.Size();
    if (tmp->value.key > key) {
        return nullptr;
    }
    for (int i = 0; i < (s - 2) ; ++i) {
        if (tmp->next->value.key > key) {
            return tmp;
        } 
        tmp = tmp->next;
    }
    return tmp;
}

template <class K, class V, int T>
void RePrev(TList <TKeyVal<K,V,T>>& keys, TNode<K,V,T>* prev) {
    if (keys.head->value.left == nullptr) {
        return;
    }
    TLNode<TKeyVal<K,V,T>>* tmp = keys.head;
    while(tmp != keys.tail) {
        tmp->value.left->prev = prev;
        tmp = tmp->next; 
    }
    tmp->value.left->prev = prev;
}

template <class K, class V, int T>
void JoinKeys(TList <TKeyVal<K,V,T>>& to, TList <TKeyVal<K,V,T>>& from, TKeyVal<K,V,T>& mid) {
    if (to.Get(0)->value.left) {
        RePrev(from, to.Get(0)->value.left->prev);
    }
    if (to.Get(0)->value.key < from.Get(0)->value.key) {
        to.Last()->value.key = mid.key;
        to.Last()->value.value = mid.value;
        to.Last()->next = from.Get(0);
        to.NTail(from.Last());
        to.ReSize();
    } else {
        from.Last()->value.key = mid.key;
        from.Last()->value.value = mid.value;
        from.Last()->next = to.Get(0);
        to.NHead(from.Get(0));
        to.ReSize();
    }
    from.NHead(nullptr);
    from.NTail(nullptr);
    from.ReSize();
}

template <class K, class V, int T>
class TNode {
    public:
        using node_ptr = TNode<K,V,T>*;
        using list_node_ptr = TLNode<TKeyVal<K,V,T>>*;

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
                    prev = new TNode<K,V,T>(nullptr, this);
                }
                list_node_ptr mid = new TLNode<TKeyVal<K,V,T>>(keys.Get(T-1));
                node_ptr left = new TNode<K,V,T>(keys.Get(0), keys.Get(T-1), prev);
                keys.NHead(mid->next);
                keys.ReSize();
                mid->value.left = left;
                prev->Plus(mid);
                RePrev(left->keys, left);
                if (key < mid->value.key) {
                    return left->add(key, val);
                }
                if (key > mid->value.key) {
                    return this->add(key, val);
                } else {
                    return 0;
                }
            }
            list_node_ptr tmp = keys.Get(0);
            int s = keys.Size();
            for (int i = 0; i < (s - 1) ; ++i) {
                if (tmp->value.key > key) {
                    if (tmp->value.left) {
                        return tmp->value.left->add(key, val);
                    } else {
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
            } else {
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
            for (int i = 0; i < (s - 2) ; ++i) {
                if (tmp->next->value.key > In->value.key) {
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
        int addFRBrother(K to) {
            list_node_ptr tmp = findKey(keys, to);
            if (tmp->next == nullptr) {
                return 0;
            }
            if (tmp->next->value.left->keys.Size() - 1 == T - 1 ) {
                return 0;
            }
            list_node_ptr right = tmp->next->value.left->keys.Get(0);
            if(right->value.left) {
                right->value.left->prev = tmp->value.left;
            }

            tmp->value.left->keys.Last()->value.key = tmp->value.key;
            tmp->value.left->keys.Last()->value.value = tmp->value.value;
            tmp->value.left->keys.PushBack(TKeyVal<K,V,T>(right->value.left));

            tmp->value.value = right->value.value;
            tmp->value.key = right->value.key;

            tmp->next->value.left->keys.Delete(0);
            return 1;
        }

        int addFLBrother(K to) {
            list_node_ptr tmp = findPrevKey(keys, to);
            if (tmp == nullptr) {
                return 0;
            }
            if (tmp->value.left->keys.Size() - 1 == T - 1 ) {
                return 0;
            }
            list_node_ptr mid = tmp->next;
            int s = tmp->value.left->keys.Size();
            if(tmp->value.left->keys.Get(s - 1)->value.left) {
                tmp->value.left->keys.Get(s - 1)->value.left->prev = mid->value.left;
            }
            mid->value.left->keys.Insert(0, TKeyVal<K,V,T>(tmp->value.key, 
                                                           tmp->value.value,
                                                           tmp->value.left->keys.Get(s - 1)->value.left));

            tmp->value.value = tmp->value.left->keys.Get(s - 2)->value.value;
            tmp->value.key = tmp->value.left->keys.Get(s - 2)->value.key;

            tmp->value.left->keys.Delete(s - 1);
            return 1;
        }

        int JoinR(K to) {
            list_node_ptr tmp = findKey(keys, to);
            if (tmp->next == nullptr) {
                return 0;
            }
            JoinKeys(tmp->value.left->keys, tmp->next->value.left->keys, tmp->value);
            delete tmp->next->value.left;
            tmp->next->value.left = tmp->value.left;
            keys.Delete(tmp);
            return 1;
        }
        int JoinL(K to) {
            list_node_ptr tmp = findPrevKey(keys, to);
            if (tmp == nullptr) {
                return 0;
            }
            JoinKeys(tmp->next->value.left->keys, tmp->value.left->keys, tmp->value);
            delete tmp->value.left;
            keys.Delete(tmp);
            return 1;
        }
        
        int AddExt() {
            if (!prev) {
                return 0;
            }
            if (prev->addFRBrother(keys.Get(0)->value.key)) {
                return 1;
            } else if (prev->addFLBrother(keys.Get(0)->value.key)) {
                return 1;
            } else if (prev->keys.Size() - 1 == T - 1) {
                prev->AddExt();
            }
            if (prev->JoinR(keys.Get(0)->value.key)) {
                return 1;
            } else if (prev->JoinL(keys.Get(0)->value.key)) {
                return 1;
            }
            return 0;
        } 

        int del(K d) {
            if (keys.Size() - 1 == T - 1) {
                AddExt();
            }
            list_node_ptr tmp = findKey(keys, d);
            if (tmp->value.key == d) {
                if (tmp->value.left == nullptr) {
                    keys.Delete(tmp);
                    return 1;
                } else {
                    if (addFRBrother(d)) {
                        return tmp->value.left->del(d);
                    } else if (addFLBrother(d)) {
                        return tmp->next->value.left->del(d);
                    } else if (JoinR(d)) {
                        return del(d);
                    } else if (JoinL(d)) {
                        return del(d);
                    }
                    return -1;
                }
            } else {
                if (tmp->value.left == nullptr) {
                    return 0;
                }
                return tmp->value.left->del(d);
            }
        }
        
        void Print(int level) {
            int s = keys.Size();
            for (int k = 0 ; k < level; k++) {
                putchar('\t');
            }
            keys.Print(s - 1);
            list_node_ptr tmp = keys.Get(0);
            for (int i = 0; i < s ; ++i) {
                if (tmp->value.left) {
                    tmp->value.left->Print(level + 1);
                }
                tmp = tmp->next;
            }
        }
        
        void Free() {

        }
       
        ~TNode() {
            list_node_ptr tmp = keys.head;
            if (!tmp) {
                return;
            }
            if (tmp->value.left) {
                while (tmp != keys.tail) {
                    delete tmp->value.left;
                    tmp = tmp->next;
                }
                delete tmp->value.left;
            }

        }
        

        TList <TKeyVal<K,V,T>> keys;
        node_ptr prev;
};

template <class K, class V, int T>
class TBTree {
    using node_ptr = TNode<K,V,T>*;
    using list_node_ptr = TLNode<TKeyVal<K,V,T>>*;
    public:
        node_ptr root;
        TBTree() {
            root = new TNode<K,V,T>(nullptr);
        }
        int add(K key, V val) {
            if (root->add(key, val)) {
                while (root->prev != nullptr) {
                    root = root->prev;
                }
                return 1;
            }
            return 0;
        }
        int del(K key) {
            return root->del(key);
        }
        void Print() {
            root->Print(0);
        }
        
        ~TBTree() {
            delete root;
        }
    private:
        //node_ptr root;
};


