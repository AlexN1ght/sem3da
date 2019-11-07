#include <iostream>
#include <cassert>


template<class T>
struct TLNode {
    T value;
    std::shared_ptr<TLNode<T> > next;
};

template<class T>
class TList {
    using node_ptr = std::shared_ptr<TLNode<T>>;

    public:
        TList(): size(0), head(nullptr), tail(nullptr) {}
        TList(node_ptr headIn, node_ptr tailIn) {
            assert(!(headIn == nullptr || tailIn == nullptr));
            head = headIn;
            tail = tailIn;
            tail->next = nullptr;
            ReSize();
        }
        int Insert(int n, T value) {
            if (n < 0 || n > size) {
                return -1;
            }
            if (n == 0) {
                node_ptr newEl{new TLNode<T>};
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
            node_ptr newEl{new TLNode<T>};
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
                head = head->next;
                size--;
                if (!head) {
                    tail = head;
                }
                return 1;
            }
                
            node_ptr itr = head;
            for (int i = 0; i < n - 1; i++) {
                itr = itr->next; 
            }
            itr->next = itr->next->next;
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
        int Size() {
            return size;
        }
    private:
        int size;
        node_ptr head;
        node_ptr tail;

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
};

