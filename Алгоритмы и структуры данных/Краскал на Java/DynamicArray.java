package org.example;

import java.util.Iterator;

public class DynamicArray<T>
        implements Iterable<T> {
    private class DynamicArrayIterator
            implements Iterator<T> {
        private int index = 0;

        public boolean hasNext() {
            return index < size();
        }

        public T next() {
            return (T) get(index++);
        }
    }

    private int defaultSize = 10;
    private int size = 0;
    private Object[] array = new Object[defaultSize];

    private void resize(int size) {
        Object[] new_array = new Object[size];
        System.arraycopy(array, 0, new_array, 0, array.length);
        array = new_array;
    }

    public void add(T obj) {
        if(size >= array.length - 1) {
            resize(array.length * 2);
        }
        array[size] = obj;
        size++;
    }

    public void remove(int index) {
        if(index < size && ! is_empty()) {
            if(size - 1 <= array.length / 4 && array.length > defaultSize) {
                resize(array.length / 2);
            }
            System.arraycopy(array, 0, array, 0, index);
            System.arraycopy(array, index + 1, array, index, array.length - index - 1);
            size--;
        }
    }

    public void remove(T obj) {
        for(int i = 0; i < size; i++) {
            if(array[i] == obj) {
                remove(i);
                break;
            }
        }
    }

    public void removeAll(T obj) {
        for(int i = 0; i < size; i++) {
            if(array[i] == obj) {
                remove(i);
            }
        }
    }

    public void clear() {
        Object[] new_array = new Object[defaultSize];
        array = new_array;
        size = 0;
    }

    public void set(T obj, int index) {
        if(index < size && ! is_empty()) {
            array[index] = obj;
        }
    }

    public boolean is_empty() {
        return size == 0;
    }

    public boolean contains(T obj) {
        for(int i = 0; i < size; i++) {
            if(array[i] == obj) {
                return true;
            }
        }

        return false;
    }

    public int indexOf(T obj) {
        for(int i = 0; i < size; i++) {
            if(array[i] == obj) {
                return i;
            }
        }

        return - 1;
    }

    public int size() {
        return this.size;
    }

    public T get(int index) {
        if(index < size && ! is_empty()) {
            return (T) array[index];
        }

        return null;
    }

    public Iterator<T> iterator() {
        return new DynamicArrayIterator();
    }
}