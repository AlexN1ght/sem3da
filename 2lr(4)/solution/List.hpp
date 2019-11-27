#include <iostream>
#include <cassert>


template<class T>
struct TLNode {
    TLNode(TLNode<T>* In) {
        value = In->value;
        next = In->next;
    }
    TLNode() {
        next = nullptr;
    }
    T value;
    TLNode<T>* next;
};

template<class T>
class TList {
    using node_ptr = TLNode<T>*;

    public:
        int size;
        TList(): size(0), head(nullptr), tail(nullptr) {}
        TList(node_ptr headIn, node_ptr tailIn) {
            assert(!(headIn == nullptr || tailIn == nullptr));
            head = headIn;
            tail = tailIn;
            tail->next = nullptr;
            ReSize();
        }
        void NHead(node_ptr H) {
            head = H;
            //ReSize();
        }
        void NTail(node_ptr Ta) {
            tail = Ta;
            if (Ta) {
                Ta->next = nullptr;
            }
            //ReSize();
        }
        int PushBack(T value) {
            node_ptr newEl{new TLNode<T>};
            newEl->value = value;
            if (tail) {
                tail->next = newEl;
            } else {
                head = newEl;
            }
            tail = newEl;
            ++size;
            return 1;
        }
        int Insert(int n, T value) {
            if (n < 0 || n > size) {
                return -1;
            }
            if (n == 0) {
                node_ptr newEl = new TLNode<T>;
                newEl->value = value;
                newEl->next = head;
                head = newEl;
                size++;
                if (tail == nullptr) {
                    tail = newEl;
                }
                return 1;
            }
                
            node_ptr tmp = head;
            for (int i = 0; i < n - 1; i++) {
                tmp = tmp->next; 
            }
            node_ptr newEl = new TLNode<T>;
            newEl->value = value;
            newEl->next = tmp->next;
            tmp->next = newEl;
            if (newEl->next == nullptr) {
                tail = newEl;
            }
            size++;
            return 1;
        }
        int Delete(int n) {
            if (n < 0 || n >= size) {
                return -1;
            }
            if (n == 0) {
                node_ptr del = head;
                head = head->next;
                size--;
                delete del;
                if (!head) {
                    tail = head;
                }
                return 1;
            }
                
            node_ptr itr = head;
            for (int i = 0; i < n - 1; i++) {
                itr = itr->next;
            }
            node_ptr del = itr->next;
            itr->next = itr->next->next;
            if (!itr->next) {
                tail = itr;
            }
            delete del;
            size--;
            return 1;
        }
        int Delete(node_ptr n) {
            if (n == head) {
                head = head->next;
                size--;
                if (!head) {
                    tail = head;
                }
                delete n;
                return 1;
            }
                
            node_ptr itr = head;
            while (itr->next != n) {
                itr = itr->next; 
            }
            itr->next = itr->next->next;
            delete n;
            if (itr->next == nullptr) {
                tail = itr;
            }
            size--;
            return 1;
        }
        node_ptr Get(int n) {
            if (n < 0 || n >= size) {
                return nullptr;
            }
            node_ptr itr = head;
            for (int i = 0; i < n; i++) {
                itr = itr->next; 
            }
            return itr;
        }
        void Print() {
            if (size == 0) {
                return;
            }
            node_ptr tmp = head;
            while(tmp != tail) {
                std::cout << tmp->value << ' ';
                tmp = tmp->next; 
            }
            std::cout << tmp->value << '\n';
        }
        void Print(int t) {
            if (size < t) {
                return;
            }
            node_ptr tmp = head;
            for (int i = 0; i < t; ++i) {
                std::cout << tmp->value << ' ';
                tmp = tmp->next; 
            }
            std::cout << '\n';
        }
        int Size() {
            return size;
        }
        node_ptr Last() {
            return tail;
        }
        /*
        int Find(T in) {
            node_ptr tmp = head;
            while(tmp != tail) {
                tmp = tmp->next; 
            }
        }
        */

        void ReSize() {
            if (!head) {
                size = 0;
            }
            int i = 1;
            node_ptr tmp = head;
            while(tmp != tail) {
                tmp = tmp->next; 
                i++;
            }
            size = i;
        }

        ~TList() {
            if (!head) {
                return;
            }
            node_ptr tmp = head;
            node_ptr next;
            while(tmp != tail) {
                next = tmp->next; 
                delete tmp;
                tmp = next;
            }
            delete tmp;
        }
        
        node_ptr head;
        node_ptr tail;
};

