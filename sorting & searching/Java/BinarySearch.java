/**
 * @file BinarySearch.java
 * @author Weilan Tao
 * @brief This is the code of the java version binary search
 * @version 1.0
 * @date 2020-10-18 EST
 *
 * @copyright Copyright (c) 2020
 *
 */


import java.util.*;

public class BinarySearch {

    /**
     * Iterative Binary Search
     * @param array
     * @param k
     * @return the index of the target value k in the array
     */
    public static int binarySearch(int[] array, int k){

        int l=0;
        int r=array.length-1;
        int mid;
        while(array[l]<array[r]){
            mid=l+(r-l)/2; // prevent overload

            if (array[mid] == k) {
                r = mid;
            }
            else {
                l = mid + 1;
            }
        }
        return l;
    }

    /**
     * bubble sort
     * @param array
     * @param len
     * return sorted array
     */
    public static void bubbleSort(int[] array,int len){
        int temp;
        for(int i =0; i<len-1; i++){
            for (int j=0;j<len-i-1;j++){
                if(array[j]>array[j+1]) {
                    temp = array[j];
                    array[j] = array[j + 1];
                    array[j + 1] = temp;
                }
            }
        }
    }

    public static void main(String args[]){
        System.out.println("enter the length of an array");
        Scanner s1= new Scanner(System.in);
        int x=s1.nextInt();
        int[] array= new int[x];

        System.out.println("initialize the array");
        for(int i=0; i<x; i++){
            array[i]=s1.nextInt();
        }
        bubbleSort(array,x);
        System.out.println("enter the target value");
        int k=s1.nextInt();
        
        //output
        System.out.println( binarySearch(array,k));
        s1.close();
    }
}
