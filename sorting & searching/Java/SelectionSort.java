/**
 * @file SelectionSort.java
 * @author Weilan Tao
 * @brief This is the code of the java version Selection Sort
 * @version 1.0
 * @date 2020-10-18 EST
 *
 * @copyright Copyright (c) 2020
 *
 */


import java.util.*;
public class SelectionSort {

    /**
     * Selection Sort
     * @param array
     * @param len
     *O(n^2)
     */
    public static void selectionSort(int[] array, int len){
        for(int i=0;  i<len ; i++){//loop through the array 0~length-1
            int minIndex=i;

            for (int j=i; j<len;j++){//loop through the unsorted part i~length-1
                if(array[j]<array[i]){
                    array[i]=array[j];
                    minIndex=j;
                }
            }

            int temp=array[i];
            array[i]=array[i];
            array[minIndex]=temp;

        }

    }


    public static void main(String args[]){
        System.out.println("enter the length of an array");
        Scanner s1= new Scanner(System.in);
        int x;
        x=s1.nextInt();

        int[] array= new int[x];
        System.out.println("set the array");

        for(int i=0; i<x; i++){
            Scanner s2= new Scanner(System.in);
            array[i]=s2.nextInt();
        }

        selectionSort(array,x);

        System.out.println("print the sorted array");
        for(int i=0; i<x; i++){
            System.out.print(array[i]);
        }
    }

}
