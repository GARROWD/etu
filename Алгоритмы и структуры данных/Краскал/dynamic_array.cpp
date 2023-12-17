#include "edge.cpp"

template<typename T>
class dynamic_array {
private:
    int default_size = 10;
    int real_size = 10;
    int size;
    T *array;

    void resize(int size) {
        if (size > 0) {
            T *tmp = new T[size];

            for (int i = 0; i < this->size; i++) {
                tmp[i] = array[i];
            }

            delete[] array;
            array = tmp;
            this->real_size = size;
        }
    }

public:
    dynamic_array() {
        size = 0;
        array = new T[default_size];
    }

    ~dynamic_array() {
        delete[] array;
    }

    void add(T obj) {
        if (size >= real_size - 1) {
            resize(real_size * 2);
        }
        array[size] = obj;
        size++;
    }

    void remove(int index) {
        if (index < size && !is_empty()) {
            if (size - 1 <= real_size / 4 && real_size > default_size) {
                resize(real_size / 2);
            }

            for (int i = 0; i < real_size - index - 1; i++) {
                array[i + index] = array[i + index + 1];
            }
            size--;
        }
    }

    void clear() {
        delete[]array;
        T new_array = new T[default_size];
        array = new_array;
        size = 0;
    }

    void set(T obj, int index) {
        if (index < size && !is_empty()) {
            array[index] = obj;
        }
    }

    bool is_empty() {
        return size == 0;
    }

    bool contains(T obj) {
        for (int i = 0; i < size; i++) {
            if (array[i] == obj) {
                return true;
            }
        }

        return false;
    }

    int index_of(T obj) {
        for (int i = 0; i < size; i++) {
            if (array[i] == obj) {
                return i;
            }
        }

        return -1;
    }

    int get_size() {
        return size;
    }

    T get(int index) {
        return (T) array[index];
    }
};
