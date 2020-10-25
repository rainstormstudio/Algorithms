/**
 * @File Quick Sort
 * @Author Weilan Tao
 * @Date 2020-10-24 EST
 * @Description This is the code for quick sort, java version.
 * @Since version-1.0
 * @Copyright Copyright (c) 2020
 */


import java.util.Scanner;

public class QuickSorting {

    /**
     * Quick Sort
     *
     * @param array
     * @param x     O(nlogn) for average case running;
     *              O(n^2) for worst case running
     */
    public static void quickSort(int[] array, int x) {
        int l = 0;
        int h = x;
        quickSort(array, l, h);
    }


    /**
     * recursion part of the Quick Sort
     *
     * @param array
     * @param l
     * @param h
     */
    public static void quickSort(int[] array, int l, int h) {
        if (l < h) {
            int j = partition(array, l, h);
            quickSort(array, l, j);
            quickSort(array, j + 1, h);
        } else ;
    }


    /**
     * partition function
     *
     * @param array
     * @param l
     * @param h
     * @return
     */
    public static int partition(int[] array, int l, int h) {
        int pivot = array[l];
        int i = l;
        int j = h;
        while (i < j) {
            while (array[i] <= pivot) {
                i++;
            }
            while (array[j] > pivot) {
                j--;
            }
            swap(array, i, j);
        }
        swap(array, i, j);
        return j;
    }

    /**
     * swap function
     *
     * @param array
     * @param a
     * @param b
     */
    public static void swap(int[] array, int a, int b) {
        int temp = array[a];
        array[a] = array[b];
        array[b] = temp;
    }


    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("enter the length of an array");
        int x = scanner.nextInt();

        int[] array = new int[x];
        System.out.println("set the array");

        for (int i = 0; i < x; i++) {
            array[i] = scanner.nextInt();
        }

        quickSort(array, x);

        System.out.println("print the sorted array");
        for (int i = 0; i < x; i++) {
            System.out.print(array[i] + " ");
        }
        scanner.close();
    }
}



