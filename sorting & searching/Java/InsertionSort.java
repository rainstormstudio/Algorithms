/**
 * @file InsertionSort.java
 * @author Weilan Tao
 * @brief This is the code of the java version Insertion Sort
 * @version 1.0
 * @date 2020-10-18 EST
 *
 * @copyright Copyright (c) 2020
 *
 */


import java.util.*;
public class InsertionSort {

    /**
     *insertion sort
     * @param array
     * @param len
     * O(n^2)
     */
    public static void insertionSort(int [] array, int len){
        for (int i=1;i<len;i++){ //loop through the array 1~len-1
            int key=array[i];
            int j=i-1;
            while(j>=0 ){//loop backwards 0~i-1
                if(key<array[j]) {//here we have to take the condition "key<array[j]" into the while loop to prevent protential  index overload
                    int temp = array[j];
                    array[j] = array[j + 1];
                    array[j + 1] = temp;
                    j--;
                }else
                    break;
            }
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

        insertionSort(array,x);

        System.out.println("print the sorted array");
        for(int i=0; i<x; i++){
            System.out.print(array[i]);
        }
    }
}
