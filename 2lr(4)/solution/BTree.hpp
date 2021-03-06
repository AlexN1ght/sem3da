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
            Kcons++;
            left = nullptr;
        }
        TKeyVal(node_ptr to) {
            Kcons++;
            left = to;
        }
        TKeyVal(K& keyIn, V& valIn): key(keyIn), value(valIn) {
            Kcons++;
            left = nullptr;
        }
        TKeyVal(K& keyIn, V& valIn, node_ptr& to): key(keyIn), value(valIn) {
            Kcons++;
            left = to;
        }
        TKeyVal(const TKeyVal<K,V,T>& in) : key(in.key){
            Kcop++;
            value = in.value;
            left = in.left;
        }
        TKeyVal(TKeyVal<K,V,T>&& in) : key(std::move(in.key)){
            Kmov++;
            value = in.value;
            left = in.left;
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
    for (int i = 0; i < (s - 1); ++i) {
        if (tmp->value->key >= key) {
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
    if (tmp->value->key > key) {
        return nullptr;
    }
    for (int i = 0; i < (s - 2) ; ++i) {
        if (tmp->next->value->key > key) {
            return tmp;
        } 
        tmp = tmp->next;
    }
    return tmp;
}

template <class K, class V, int T>
void RePrev(TList <TKeyVal<K,V,T>>& keys, TNode<K,V,T>* prev) {
    if (keys.head->value->left == nullptr) {
        return;
    }
    TLNode<TKeyVal<K,V,T>>* tmp = keys.head;
    while(tmp != keys.tail) {
        tmp->value->left->prev = prev;
        tmp = tmp->next; 
    }
    tmp->value->left->prev = prev;
}

template <class K, class V, int T>
void JoinKeys(TList <TKeyVal<K,V,T>>& to, TList <TKeyVal<K,V,T>>& from, TKeyVal<K,V,T>* mid) {
    if (to.Get(0)->value->left) {
        RePrev(from, to.Get(0)->value->left->prev);
    }
    if (to.Get(0)->value->key < from.Get(0)->value->key) {
        to.Last()->value->key = mid->key;
        to.Last()->value->value = mid->value;
        to.Last()->next = from.Get(0);
        to.NTail(from.Last());
        to.ReSize();
    } else {
        from.Last()->value->key = mid->key;
        from.Last()->value->value = mid->value;
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

        TNode() {
            prev = nullptr;
        }
        TNode(node_ptr from) {
            prev = from;
            keys.Insert(0, new TKeyVal<K,V,T>());
        }
        TNode(node_ptr from, node_ptr to) {
            prev = from;
            keys.Insert(0, new TKeyVal<K,V,T>(to));
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
                mid->value->left = left;
                prev->Plus(mid);
                RePrev(left->keys, left);
                if (key < mid->value->key) {
                    return left->add(key, val);
                }
                if (key > mid->value->key) {
                    return this->add(key, val);
                } else {
                    return 0;
                }
            }
            list_node_ptr tmp = keys.Get(0);
            int s = keys.Size();
            for (int i = 0; i < (s - 1) ; ++i) {
                if (tmp->value->key > key) {
                    if (tmp->value->left) {
                        return tmp->value->left->add(key, val);
                    } else {
                        keys.Insert(i, new TKeyVal<K,V,T>(key, val));
                        return 1;
                    }
                } else if (tmp->value->key == key) {
                    return 0;
                }
                tmp = tmp->next;
            }
            if (tmp->value->left) {
                return tmp->value->left->add(key, val);
            } else {
                keys.Insert(s - 1, new TKeyVal<K,V,T>(key, val));                
                return 1;
            }
        }
        void Plus(list_node_ptr In) {
            list_node_ptr tmp = keys.Get(0);
            int s = keys.Size();
            if (tmp->value->key > In->value->key || s == 1) {
                In->next = tmp;
                keys.NHead(In);
                ++(keys.size);
                return;
            }
            for (int i = 0; i < (s - 2); ++i) {
                if (tmp->next->value->key > In->value->key) {
                    In->next = tmp->next;
                    tmp->next = In;
                    ++(keys.size);
                    return;
                }
                tmp = tmp->next;
            }
            In->next = tmp->next;
            tmp->next = In;
            ++(keys.size);
        }
        int addFRBrother(K& to) {
            list_node_ptr tmp = findKey(keys, to);
            if (tmp->next == nullptr) {
                return 0;
            }
            if (tmp->next->value->left->keys.Size() - 1 <= T - 1 ) {
                return 0;
            }
            list_node_ptr right = tmp->next->value->left->keys.Get(0);
            if(right->value->left) {
                right->value->left->prev = tmp->value->left;
            }

            tmp->value->left->keys.Last()->value->key = tmp->value->key;
            tmp->value->left->keys.Last()->value->value = tmp->value->value;
            tmp->value->left->keys.PushBack(new TKeyVal<K,V,T>(right->value->left));

            tmp->value->value = right->value->value;
            tmp->value->key = right->value->key;

            tmp->next->value->left->keys.Delete(0);
            return 1;
        }

        int addFLBrother(K& to) {
            list_node_ptr tmp = findPrevKey(keys, to);
            if (tmp == nullptr) {
                return 0;
            }
            if (tmp->value->left->keys.Size() - 1 <= T - 1 ) {
                return 0;
            }
            list_node_ptr mid = tmp->next;
            int s = tmp->value->left->keys.Size();
            if(tmp->value->left->keys.Get(s - 1)->value->left) {
                tmp->value->left->keys.Get(s - 1)->value->left->prev = mid->value->left;
            }
            mid->value->left->keys.Insert(0,new TKeyVal<K,V,T>(tmp->value->key, 
                                                           tmp->value->value,
                                                           tmp->value->left->keys.Get(s - 1)->value->left));

            tmp->value->value = tmp->value->left->keys.Get(s - 2)->value->value;
            tmp->value->key = tmp->value->left->keys.Get(s - 2)->value->key;

            tmp->value->left->keys.Delete(s - 1);
            return 1;
        }

        int JoinR(K& to) {
            list_node_ptr tmp = findKey(keys, to);
            if (tmp->next == nullptr) {
                return 0;
            }
            JoinKeys(tmp->value->left->keys, tmp->next->value->left->keys, tmp->value);
            delete tmp->next->value->left;
            tmp->next->value->left = tmp->value->left;
            keys.Delete(tmp);
            return 1;
        }
        int JoinL(K& to) {
            list_node_ptr tmp = findPrevKey(keys, to);
            if (tmp == nullptr) {
                return 0;
            }
            JoinKeys(tmp->next->value->left->keys, tmp->value->left->keys, tmp->value);
            delete tmp->value->left;
            keys.Delete(tmp);
            return 1;
        }
        
        int AddExt() {
            if (!prev) {
                return 0;
            }
            if (prev->addFRBrother(keys.Get(0)->value->key)) {
                return 1;
            } else if (prev->addFLBrother(keys.Get(0)->value->key)) {
                return 1;
            } else if (prev->JoinR(keys.Get(0)->value->key)) {
                return 1;
            } else if (prev->JoinL(keys.Get(0)->value->key)) {
                return 1;
            }
            return 0;
        } 

        int del(K& d) {
            if (keys.Size() - 1 == T - 1) {
                AddExt();
            }
            list_node_ptr tmp = findKey(keys, d);
            if (tmp->value->key == d && tmp->next) {
                if (!tmp->value->left) {
                    keys.Delete(tmp);
                    return 1;
                } else {
                    if (addFRBrother(d)) {
                        return tmp->value->left->del(d);
                    } else if (addFLBrother(d)) {
                        return tmp->next->value->left->del(d);
                    } else if (JoinR(d)) {
                        return del(d);
                    } else if (JoinL(d)) {
                        return del(d);
                    }
                    return -1;
                }
            } else {
                if (tmp->value->left == nullptr) {
                    return 0;
                }
                return tmp->value->left->del(d);
            }
        }
        
        V Find(K& in) {
            list_node_ptr tmp = findKey(keys, in);
            if (!tmp) {
                throw -1;
            }
            if (tmp->value->key == in && tmp->next) {
                return tmp->value->value;
            } else if (tmp->value->left) {
                return tmp->value->left->Find(in);
            }
            throw -1;
        }

        void Print(int level) {
            int s = keys.Size();
            for (int k = 0 ; k < level; k++) {
                putchar('\t');
            }
            keys.Print(s - 1);
            list_node_ptr tmp = keys.Get(0);
            for (int i = 0; i < s ; ++i) {
                if (tmp->value->left) {
                    tmp->value->left->Print(level + 1);
                }
                tmp = tmp->next;
            }
        }

        int Save(FILE* stor) {
            int s = keys.Size();
            fwrite(&s, sizeof(int), 1, stor);

            list_node_ptr tmp = keys.Get(0);
            for (int i = 0; i < (s - 1) ; ++i) {
                fwrite(tmp->value->key.CStr(), 257, 1, stor);
                fwrite(&tmp->value->value, sizeof(V), 1, stor);
                tmp = tmp->next;
            }

            int end = ((keys.Get(0)->value->left) ? 0 : 1);
            fwrite(&end, sizeof(int), 1, stor);
            tmp = keys.Get(0);
            if (!end) {
                for (int i = 0; i < s ; ++i) {
                    tmp->value->left->Save(stor);
                    tmp = tmp->next;
                }
            }
            return 1;
        }
        
        int Load(FILE* stor) {
            int s;
            fread(&s, sizeof(int), 1, stor);
            K key;
            V val;
            for (int i = 0; i < (s - 1) ; ++i) {
                fread(key.CStr(), 257, 1, stor);
                fread(&val, sizeof(V), 1, stor);
                keys.PushBack(new TKeyVal<K,V,T>(key, val));
            }
            keys.PushBack(new TKeyVal<K,V,T>(nullptr));

            int end;
            fread(&end, sizeof(int), 1, stor);
            list_node_ptr tmp = keys.Get(0);
            if (!end) {
                for (int i = 0; i < s ; ++i) {
                    tmp->value->left = new TNode<K,V,T>();
                    tmp->value->left->Load(stor);
                    tmp->value->left->prev = this;
                    tmp = tmp->next;
                }
            }
            return 1;
        }
        
        ~TNode() {
            list_node_ptr tmp = keys.head;
            if (!tmp) {
                return;
            }
            if (tmp->value->left) {
                while (tmp != keys.tail) {
                    delete tmp->value->left;
                    tmp = tmp->next;
                }
                delete tmp->value->left;
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
        int add(K& key, V& val) {
            if (root->add(key, val)) {
                while (root->prev != nullptr) {
                    root = root->prev;
                }
                return 1;
            }
            while (root->prev != nullptr) {
                root = root->prev;
            }
            return 0;
        }
        int del(K& key) {
            if (root->del(key)) {
                if (root->keys.Size() == 1) {
                    node_ptr tmp = root->keys.head->value->left;
                    if (!tmp) {
                        return 1;
                    }
                    root->keys.head->value->left = nullptr;
                    delete root;
                    root = tmp;
                    root->prev = nullptr;
                }
                return 1;
            }
            return 0;
        }
        void Print() {
            root->Print(0);
        }
        V Find(K& in) {
            return root->Find(in);
        }
        int Save(char* path) {
            FILE* stor = fopen(path, "wb");
            if (!stor) {
                return 0;
            }
            root->Save(stor);
            fclose(stor);
            return 1;
        }
        int Load(char* path) {
            FILE* stor = fopen(path, "rb");
            if (!stor) {
                return 0;
            }
            delete root;
            root = new TNode<K,V,T>();
            root->Load(stor);
            fclose(stor);
            return 1;
        }
        
        ~TBTree() {
            delete root;
        }
};


