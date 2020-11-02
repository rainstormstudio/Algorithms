/**
 * @File DisjointSets.java
 * @Author Weilan Tao
 * @Date 2020-11-1
 * @Description This is the implementation for Disjoint Sets, java version.
 * @Since version-1.0
 * @Copyright Copyright (c) 2020
 */


import java.util.ArrayList;

public class DisjointSets {

    private static ArrayList<Integer> parent;
    private static ArrayList<Integer> rank;
    private static int numOfSets;

    DisjointSets(int max) {
        this.numOfSets = max;
        this.rank = new ArrayList<Integer>(max);
        this.parent = new ArrayList<Integer>(max);

        for (int i = 0; i < max; i++) {
            parent.add(i);
            rank.add(-1);
        }


    }

    public static int getNumOfSets() {
        return numOfSets;
    }


    /**
     *
     * @param i, the element
     * @return the the root of an element.
     */
    public static int find(int i) {
        if (parent.get(i) == i) return i;
        else return find(parent.get(i));
    }

    public static void union(int i, int j) {
        int fi = find(i);
        int fj = find(j);
        if (isCycle(i, j)) {
            System.out.println("These two nodes have the same parent. Will form a cycle. Cannot do union operation.");
        } else {
            if (Math.abs(rank.get(fi)) >= Math.abs(rank.get(fj))) {
                rank.set(fi, rank.get(fi) + rank.get(fj));
                parent.set(j, find(i));
                numOfSets--;
            } else {
                rank.set(fj, rank.get(fi) + rank.get(fj));
                parent.set(i, find(j));
                numOfSets--;
            }

        }

    }

    public static boolean isCycle(int i, int j) {
        return find(i) == find(j);
    }


}

class TestDisjointSet {
    public static void main(String[] args) {
        DisjointSets ds = new DisjointSets(8);
        System.out.println("numOfSets().." + ds.getNumOfSets());
        ds.union(0, 1);
        ds.union(2, 3);
        ds.union(4, 5);
        ds.union(6, 7);
        System.out.println("isCycle().." + ds.isCycle(1, 7));
        System.out.println("numOfSets().." + ds.getNumOfSets());
        System.out.println("find(5).." + ds.find(5));
        System.out.println("find(0).." + ds.find(0));
        ds.union(0, 2);
        System.out.println("numOfSets().." + ds.getNumOfSets());
        ds.union(3, 4);
        System.out.println("numOfSets().." + ds.getNumOfSets());
        System.out.println("find(4).." + ds.find(4));
        System.out.println("find(5).." + ds.find(5));
        System.out.println("find(6).." + ds.find(6));
        System.out.println("find(7).." + ds.find(7));
        ds.union(0, 2);
        System.out.println("numOfSets().." + ds.getNumOfSets());
        System.out.println("isCycle().." + ds.isCycle(1, 3));
        ds.union(5, 6);
        System.out.println("numOfSets().." + ds.getNumOfSets());
        System.out.println("isCycle().." + ds.isCycle(0, 7));
        System.out.println("find(0).." + ds.find(0));
        System.out.println("find(1).." + ds.find(1));
        System.out.println("find(2).." + ds.find(2));
        System.out.println("find(3).." + ds.find(3));
        System.out.println("find(4).." + ds.find(4));
        System.out.println("find(5).." + ds.find(5));
        System.out.println("find(6).." + ds.find(6));
        System.out.println("find(7).." + ds.find(7));


    }
}