/**
 * @file dynamic_array.cc
 * @author Hongyu Ding
 * @brief This is an implementation of dynamic array
 * @version 0.1
 * @date 2020-10-24
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include <iostream>

template <typename T>
class DArray {
    T* array;
    int capacity;
    int size;
public:
    DArray() : capacity{8}, size{0} {
        array = new T[capacity];
        clean();
    }
    DArray(T* a, int n) : capacity{n}, size{n} {
        array = new T[n];
        for (int i = 0; i < n; i ++) {
            array[i] = a[i];
        }
    }
    ~DArray() {
        delete[] array;
    }

    void clean() {
        for (int i = 0; i < size; i ++) {
            array[i] = 0;
        }
    }

    int getCapacity() const { return capacity; }
    int getSize() const { return size; }
    bool isEmpty() const { return size == 0; }

    T operator[](int i) const { return array[i]; }
    void set(int i, T value) {
        array[i] = value;
    }

    void add(T val) {
        if (size + 1 >= capacity) {
            if (capacity == 0) {
                capacity = 1;
            } else {
                capacity *= 2;
            }
            T* newArray = new T[capacity];
            for (int i = 0; i < size; i ++) {
                newArray[i] = array[i];
            }
            delete [] array;
            array = newArray;
        }
        array[size] = val;
        size ++;
    }

    T removeAt(int removeIndex) {
        T* newArray = new T[capacity];
        int index = 0;
        int removed = 0;
        for (int i = 0; i < size; i ++) {
            if (removeIndex != i) {
                newArray[index] = array[i];
                index ++;
            } else {
                removed = array[i];
            }
        }
        delete[] array;
        array = newArray;
        size --;
        return removed;
    }

    int indexOf(T val) {
        for (int i = 0; i < size; i ++) {
            if (array[i] == val) {
                return i;
            }
        }
        return -1;
    }

    bool contains(T val) {
        return indexOf(val) != -1;
    }

    void print(std::ostream& out) {
        if (isEmpty()) {
            out << "[]";
            return;
        }
        out << "[" << array[0];
        for (int i = 1; i < size; i ++) {
            out << ", " << array[i];
        }
        out << "]";
    }
};

int main() {
    DArray<int> array;
    array.add(2);
    array.add(5);
    array.add(6);
    array.add(1);
    array.add(-3);
    array.print(std::cout);
    array.removeAt(3);
    array.print(std::cout);
    return 0;
}
