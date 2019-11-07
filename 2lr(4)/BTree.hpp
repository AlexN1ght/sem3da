#include<algorithm>

template <class K, class V>
class TKeyNode;
template <class K, class V>
class TNode;
template <class K, class V>
class TBTree;

template <class K, class V>
class TKeyVal {
    public:
        TKeyVal() {
            key = NULL;
            &left = nullptr;
        }
        TKeyVal(K keyIn, V valIn): key(keyIn), value(valIn) {}
    private:
        K key;
        V value;
        TNode<K,V>& left; 
};


template <class K, class V, int T>
class TBTree {
    using node_ptr = std::shared_ptr<TNode<K,V,T>>;
    using list_node_ptr = std::shared_ptr<TLNode<T>>;
    public:
        TBTree() {
             root = new TNode<K,V,T>(nullptr);
        }
        int add(K, V) {
            root.add;
        }
        void print() {

        }
    private:
        struct TNode {
            TNode(TNode<K,V> from) {
                &prev = from;
                keys.push_back(TKeyVal<K,V>());
            }
            int add (K key, V val){
                if (keys.Size() == 2 * T) {
                    list_node_ptr mid = keys.Get(T-1).
                    node_ptr left = new TNode<K,V,T>(keys.Get(0), keys.Get(T-1));
                    keys.NHead(mid->next);
                    prev.Plus(mid, left);
                    if (key < mid.value.key)
                        return left.add(key, val);
                    if (key > mid.value.key)
                        return this.add(key, val);
                    else
                        return -1;
                }
            }
            int Plus(list_node_ptr In, node_ptr left)
            TList <TKeyVal<K,V>> keys;
            node_ptr prev;
    };
        node_ptr root;
};


