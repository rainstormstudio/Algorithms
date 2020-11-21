/**
 * @File Heap.java
 * @Author Weilan Tao
 * @Date 2020-11-19
 * @Description This is the implementation for Max Heap, Java version.
 * @Since version-1.1
 * @Copyright Copyright (c) 2020
 */

public class Heap {

    public static int[] array;
    private static int len;
    private static int heapLen;

    public Heap() {
        this.len = 1;
        this.array = new int[len];
        array[0] = 0;
        heapLen = len;
    }

    public static int getHeapLen() {
        return heapLen - 1;
    }

    public static void getHeap() {
        for (int i = 1; i < heapLen; i++) {
            System.out.print(array[i] + " ");
        }
        System.out.println(" ");
    }

    public static int parentIndex(int index) {
        return index / 2;
    }

    public static int leftChild(int index) {
        return index * 2;
    }

    public static int rightChild(int index) {
        return index * 2 + 1;
    }

    public static void swap(int indexA, int indexB, int[] array) {
        int temp = array[indexA];
        array[indexA] = array[indexB];
        array[indexB] = temp;
    }

    /**
     * Time complexity of insertion is O(logn)
     * Time complexity of heap creation is O (nlogn)
     *
     * @param val
     */
    public static void Insert(int val) {
        // extent array
        len = len + 1;
        heapLen++;
        array = java.util.Arrays.copyOf(array, array.length + 1);
        int newIndex = len - 1;
        array[newIndex] = val;

        if (heapLen < len) {
            int temp = len - 1;

            while (temp > heapLen - 1) {
                swap(temp, temp - 1, array);
                temp--;
            }

            newIndex = temp;
            array[newIndex] = val;

        }
        int pIndex = parentIndex(newIndex);


        while (pIndex != 0) {

            if (val > array[pIndex]) {
                swap(newIndex, pIndex, array);
                newIndex = pIndex;
                pIndex = parentIndex(newIndex);
            } else {
                break;
            }
        }
    }


    public static void pop() {
        if (getHeapLen() == 0) {
            System.out.println("The heap is empty. Cannot do pop.");
            return;
        }

        //swap the nodes
        System.out.println("Pop...the first node of the heap contains value..." + array[1]);
        swap(1, heapLen - 1, array);
        heapLen = heapLen - 1;
        //adjust the heap
        int temphead = 1;
        int biggerIndex;

        while ((leftChild(temphead) <= heapLen - 1) || (rightChild(temphead) <= heapLen - 1)) {
            if ((rightChild(temphead) < heapLen)) {
                if (array[leftChild(temphead)] >= array[rightChild(temphead)]) {
                    biggerIndex = leftChild(temphead);
                } else {
                    biggerIndex = rightChild(temphead);
                }
                if (array[biggerIndex] > array[temphead]) {
                    swap(temphead, biggerIndex, array);
                    temphead = biggerIndex;
                } else {
                    break;
                }
            } else if ((leftChild(temphead) <= heapLen - 1) && (rightChild(temphead) > heapLen - 1)) {
                biggerIndex = leftChild(temphead);
                if (array[biggerIndex] > array[temphead]) {
                    swap(temphead, biggerIndex, array);
                    temphead = biggerIndex;
                } else {
                    break;
                }
            } else {
                break;
            }
        }
    }

    public static void peek() {
        if (getHeapLen() == 0) {
            System.out.println("The heap is empty. Cannot do peek.");
            return;
        }

        System.out.println("Peek...the first node of the heap contains value..." + array[1]);
        System.out.print("Now printing the heap after implementing the peek() operation...");
        getHeap();
    }

    /**
     * Time complexity of O(nlogn)
     */
    public static void heapSort() {
        if (getHeapLen() == 0) {
            System.out.println("The heap is empty. Cannot do heap sort.");
            return;
        } else {
            System.out.println("/////heapSort().../////");
            int t = heapLen;
            int l = heapLen - 1;
            while (l >= 1) {
                pop();
                l--;

            }

            //reverse array
            for (int i = 1; i < t / 2; i++) {
                swap(i, t - i, array);
            }


            for (int j = 1; j < t; j++) {
                System.out.print(array[j] + " ");
            }

            System.out.println("\n" + "/////end...heapSort()/////");

        }


    }

}

class TestHeap {
    public static void main(String[] args) {
        Heap maxHeap = new Heap();
        maxHeap.Insert(10);
        maxHeap.Insert(20);
        maxHeap.Insert(15);
        maxHeap.Insert(30);
        maxHeap.Insert(40);
        maxHeap.getHeap();
        System.out.println(maxHeap.getHeapLen());
        maxHeap.pop();
        maxHeap.Insert(66);
        maxHeap.getHeap();
        maxHeap.Insert(16);
        maxHeap.getHeap();
        maxHeap.pop();
        maxHeap.getHeap();
        maxHeap.heapSort();
        System.out.println(maxHeap.getHeapLen());
        maxHeap.heapSort();
        maxHeap.Insert(23);
        maxHeap.Insert(114);
        maxHeap.Insert(90);
        maxHeap.Insert(1);
        maxHeap.Insert(20);
        maxHeap.heapSort();
        maxHeap.heapSort();
        maxHeap.pop();
        maxHeap.peek();
        System.out.println(maxHeap.getHeapLen());

    }
}