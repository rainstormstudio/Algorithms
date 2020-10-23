/**
 *
 * @File Merge Sort
 * @Author Weilan Tao
 * @Date 2020-10-23
 * @Description This is the code for merge sort, java version.
 * @Since version-1.1
 * @Copyright Copyright (c) 2020
 */


import java.util.Arrays;
import java.util.Scanner;

public class MergeSort {

    /**
     * merge sort
     *
     * @param array
     * @param len
     * O(nlogn) in worst case
     */
    public static void mergeSort(int[] array, int len) {
        if (len > 1) {
            int mid = len / 2;
            mergeSort(array, mid, len);
        } else ;
    }

    /**
     * recursion part of the merge sort， return merged sub-array
     *
     * @param array
     * @param mid
     * @param len
     */
    public static void mergeSort(int[] array, int mid, int len) {
        if (len == 1) ;
        else {
            int[] l = new int[mid];
            int[] r = new int[len - mid];
            int lmid = mid / 2;
            int rmid = (len - mid) / 2;
            System.arraycopy(array, 0, l, 0, mid);
            System.arraycopy(array, mid, r, 0, len - mid);

            mergeSort(l, lmid, mid);
            mergeSort(r, rmid, len - mid);
            merge(l, r, array);
        }
    }

    /**
     * merge two sorted sub-arrays
     *
     * @param l the left sorted array
     * @param r the right sorted array
     * @param a the target merged array
     */
    public static void merge(int[] l, int[] r, int[] a) {
        int i = 0;
        int j = 0;
        int k = 0;

        while (i < l.length && j < r.length) {
            if (l[i] < r[j]) {
                a[k] = l[i];
                i++;
            } else {
                a[k] = r[j];
                j++;
            }
            k++;
        }

        while (i < l.length) {
            a[k] = l[i];
            i++;
            k++;
        }

        while (j < r.length) {
            a[k] = r[j];
            j++;
            k++;
        }

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

        mergeSort(array, x);

        System.out.println("print the sorted array" + Arrays.toString(array));
        scanner.close();
    }
}
