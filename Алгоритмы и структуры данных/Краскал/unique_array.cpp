#include "dynamic_array.cpp"

template<typename K, typename V>
class unique_array {
private:
    struct node {
        K key;
        V value;

        node() {

        }

        node(K key, V value) {
            this->key = key;
            this->value = value;
        }
    };

    dynamic_array<node> array;
    node none;
public:
    bool is_empty() {
        return array.get_size();
    }

    bool put(K key, V value) {
        for (int i = 0; i < array.get_size(); i++) {
            if (key == array.get(i).key) {
                node tmp(key, value);
                array.set(tmp, i);
                return true;
            }
        }

        node tmp(key, value);
        array.add(tmp);
        return true;
    }

    void remove(K key) {
        for (int i = 0; i < array.get_size(); i++) {
            if (array.get(i).key == key) {
                array.remove(i);
                break;
            }
        }
    }


    int get_size() {
        return array.get_size();
    }

    V get(K key) {
        for (int i = 0; i < array.get_size(); i++) {
            if (array.get(i).key == key) {
                return array.get(i).value;
            }
        }

        return none.value;
    }
};