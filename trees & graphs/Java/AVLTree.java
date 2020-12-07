/**
 * @File AVLTree.java
 * @Author Weilan Tao
 * @Date 2020-12-07
 * @Description This is the implementation for AVL Tree, Java version.
 * @Since version-1.1
 * @Copyright Copyright (c) 2020
 */


public class AVLTree {
    private Node root;
    private int size;

    class Node {
        Integer val, bf, h;
        Node left, right;

        Node(Integer i) {
            val = i;
            left = null;
            right = null;
            h=0;
            bf=0;
        }
    }

    public AVLTree() {
        size = 0;
        root=null;
    }

    public int getSize() {
        return size;
    }

    public void insert(Integer val) {
        if (val == null) {
            return;
        }

        if (isContain(val)) {
            System.out.println("This value is already in the tree.Cannot insert");
            return;
        }

        Node node = insert(root, val);

        update(node);

        size++;

    }

    private Node insert(Node node, Integer val) {

        if (node == null ) {
            return new Node(val);
        }

        if (node.val > val) {
            node.left = insert(node.left, val);
        } else if (node.val < val) {
            node.right = insert(node.right, val);
        }

        balance(node);

        return node;
    }

    private void balance(Node node){
        int bf=node.bf;

        if(bf==-2){
            rrRotation(node);
        }else if (bf==-1){
            rlRotation(node);
        }else if(bf==1){
            lrRotation(node);
        }
        else if(bf==2){
            llRotation(node);
        }else{
            return;
        }

    }

    private void llRotation(Node node) {

    }

    private void lrRotation(Node node) {

    }

    private void rrRotation(Node node) {

    }

    private void rlRotation(Node node) {

    }

    private void update(Node node) {
        updateH(node);
        updateBf(node);
    }

    private void updateH(Node node){
        node.h=Math.max(node.left.h,node.right.h)+1;
    }

    private void updateBf(Node node){
        node.bf=node.left.bf-node.right.bf;
    }


    public void remove(Integer val) {

    }

    private void remove(Node node, Integer val) {

    }

    public void print() {
        if (root == null) {
            return;
        } else {
            print(root.right, "    ", true);
            System.out.println("+---" + root.val);
            print(root.left, "    ", false);
        }

    }

    private void print(Node node, String pfx, boolean isRight) {
        if (node == null) {
            return;
        }

        print(node.right, pfx + (isRight ? "    " : "|   "), true);
        System.out.println("+---" + node.val);
        print(node.left, pfx + (isRight ? "|   " : "    "), false);

    }

    /**
     * height at most 1.44logn
     *
     * @return
     */
    public int height() {
        if (root == null) {
            return 0;
        } else {
            return root.h;
        }
    }

    public boolean isContain(Integer val) {
        return search(root, val) == null ? false : true;
    }

    /**
     * time complexity as O(logn)
     *
     * @param i
     */
    private Node search(Node node, Integer i) {
        if (i == null || node == null) {
            return null;
        }
        Node temp = root;
        while (temp != null) {
            if (temp.val == i) {
                return temp;
            }
        }
        return null;
    }


}

class TestAVLTree {
    public static void main(String args[]) {
        AVLTree avlTree = new AVLTree();
        avlTree.insert(40);
        avlTree.insert(20);
        avlTree.insert(10);
        avlTree.insert(25);
        avlTree.insert(30);
        avlTree.insert(22);
        avlTree.insert(50);
        avlTree.print();
        avlTree.height();
        avlTree.remove(101);
        avlTree.remove(30);
        avlTree.print();
        avlTree.height();
    }
}