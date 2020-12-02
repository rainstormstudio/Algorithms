/**
 * @File BinarySearchTree.java
 * @Author Weilan Tao
 * @Date 2020-12-02
 * @Description This is the implementation for Binary Search Tree, Java version.
 * @Since version-1.0
 * @Copyright Copyright (c) 2020
 */


public class BinarySearchTree {
    private Node root;
    private int size;
    private static String STR = Character.toString((char)47);
    private static String STR1 = Character.toString((char)92);

    class Node{
        int value;
        Node left;
        Node right;

        Node (Integer value){
            this.value=value;
            right=null;
            left=null;
        }
    }
    public  BinarySearchTree(){
        Node root;  //为什么？

    }

    public void insert(int val ){
        root =insertRec(root, val);
    }

    private Node insertRec(Node node, int val){
        if(node==null){
            return new Node(val);
        }

        if(node.value==val){
            return node;
        }else if(node.value<val){
            node.right=insertRec(node.right,val);
        }else{
            node.left=insertRec(node.left,val);
        }
        size++;
        return node;
    }



    public  void printTree(){
        printTreeREC(root);
    }

    //TODO Adjust the position
    private void printTreeREC(Node node){
        if(node==null){
            System.out.println("invalid node");
            return;
        }

        if(node.left!=null&&node.right!=null){
            System.out.println(node.value);
            System.out.println(STR);
            printTreeREC(node.left);
            System.out.println(STR1);
//            printTreeREC(node.left);
            printTreeREC(node.right);
        }else if(node.left!=null&&node.right==null){
            System.out.println(node.value);
            System.out.println(STR);
            printTreeREC(node.left);
        }else if(node.left==null&&node.right!=null){
            System.out.println(node.value);
            System.out.println(STR1);
            printTreeREC(node.right);
        }else{
            System.out.println(node.value);
        }


    }

    public void inOrder(){

    }

    public Node search(int value){

        return null;
    }

    public Node getMin(Node node){

        return null;
    }

    public void remove(int value){


    }


}

class TestBST{
    public static void main(String [] args){
        BinarySearchTree bst = new BinarySearchTree();
        bst.insert(20);
        bst.insert(10);
        bst.insert(30);
        bst.insert(40);
        bst.insert(9);
        bst.printTree();
    }
}
