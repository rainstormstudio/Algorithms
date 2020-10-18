/**
 * @file BubbleSort.java
 * @author Weilan Tao
 * @brief This is the code of the java version Bubble Sort
 * @version 1.0
 * @date 2020-10-17 EST
 *
 * @copyright Copyright (c) 2020
 *
 */


import java.util.*;

public class BubbleSort{

    /**
     * bubble sort
     * @param array
     * @param len
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
        int x;
        x=s1.nextInt();

        int[] array= new int[x];
        System.out.println("set the array");

        for(int i=0; i<x; i++){
            Scanner s2= new Scanner(System.in);
            array[i]=s2.nextInt();
        }

        bubbleSort(array,x);

        System.out.println("print the sorted array");
        for(int i=0; i<x; i++){
            System.out.print(array[i]);
        }

    }

}