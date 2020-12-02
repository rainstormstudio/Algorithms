/**
 * @File DynamicArray.java
 * @Author Weilan Tao
 * @Date 2020-12-02
 * @Description This is the implementation for Dynamic Array, Java version.
 * @Since version-1.0
 * @Copyright Copyright (c) 2020
 */


import java.util.Arrays;

public class DynamicArray<T> {
    private T[] array;
    private int capacity;
    private int size;

    public DynamicArray() {
        capacity = 8;
        size = 0;
        array = (T[]) new Object[capacity];

    }

    public int getCapacity() {
        return capacity;
    }

    public int getSize() {
        return size;
    }

    public boolean isEmpty() {
        return size == 0;
    }


    public void clean() {
        int temp = size;
        for (int i = 0; i < temp; i++) {
            array[i] = null;
            size--;
        }
        capacity = 0;
    }

    public void setVal(int i, T t) {
        if (i < capacity) {
            array[i] = t;
        } else {
            System.out.println("index out of bounds");
        }
    }

    public void add(T t) {
        if (size < capacity) {
            array[size] = t;
            size++;
        } else {
            if (capacity == 0) {
                capacity = 1;
            } else {
                capacity *= 2;
            }
            T[] newarr = (T[]) new Object[capacity];
            System.arraycopy(array, 0, newarr, 0, size);
            newarr[size] = t;
            array = newarr;
            size++;
        }
    }

    public void removeAt(int index) {
        T[] removed = (T[]) new Object[capacity];
        size--;
        System.arraycopy(array, 0, removed, 0, index);
        System.arraycopy(array, index + 1, removed, index, capacity - index - 1);
        removed[capacity - 1] = null;
        array = removed;
    }

    public int indexOf(T t) {
        int index = -1;
        for (T data : array) {
            index++;
            if (data == (t)) {
                return index;
            }
        }
        return index;
    }

    public boolean contains(T val) {
        return indexOf(val) == -1;
    }

    public void print() {
        System.out.println(Arrays.toString(array));
    }

}

class TestDynamicArray {
    public static void main(String[] args) {
        DynamicArray<Integer> da = new DynamicArray<>();
        da.add(2);
        da.add(5);
        da.add(6);
        da.add(1);
        da.add(-3);
        da.add(-0);
        da.add(-9);
        da.add(100);
        da.add(20);
        da.print();
        System.out.println("getCapacity()..." + da.getCapacity());
        System.out.println("getSize()..." + da.getSize());
        System.out.println("indexOf()..." + da.indexOf(100));
        System.out.println("contains()..." + da.contains(101));

        da.removeAt(2);
        da.print();
        System.out.println("getCapacity()..." + da.getCapacity());
        System.out.println("getSize()..." + da.getSize());

        da.clean();
        System.out.println(da.isEmpty());
        da.print();

        da.add(19);
        da.print();
        System.out.println("getCapacity()..." + da.getCapacity());
        System.out.println(("getSize()..." + da.getSize()));

        da.setVal(2, 90);

    }
}
