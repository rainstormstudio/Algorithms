/**
 * @File AVLTree.java
 * @Author Weilan Tao
 * @Date 2020-12-06
 * @Description This is the implementation for AVL Tree, Java version.
 * @Since version-1.0
 * @Copyright Copyright (c) 2020
 */


public class AVLTree {
    private Node root;
    private int size;

    public AVLTree(){
        size=0;
    }

    class Node{
        Integer val, bf, h;
        Node left, right;

        Node(Integer i){
            val=i;
            left=null;
            right=null;
        }
    }

    public void insert(Integer val){
        if(val==null){
            return;
        }

        if(isContain(val)){
            System.out.println("This value is already in the tree.Cannot insert");
            return;
        }

        insert(root, val);

        size++;

    }

    //FIXME
    private Node insert(Node node, Integer val){

        if(node==null){
            return new Node(val);
        }

        if(node.val>val){
            node.left=insert(node.left, val);
        }else if (node.val<val){
            node.right=insert(node.right,val);
        }

        return node;
    }

    private void rotation(){

    }

    private void llRotation(){

    }

    private void lrRotation(){

    }

    private void rrRotation(){

    }

    private void rlRotation(){

    }

    //TODO
    public void remove(Integer val){

    }

    private void remove (Node node, Integer val){

    }

    public void print(){
        if (root ==null){
            return;
        }else{
            print(root.right,"    ",true);
            System.out.println("+---"+root.val);
            print(root.left,"    ", false);
        }

    }

    private void print (Node node, String pfx, boolean isRight){
        if (node==null){
            return ;
        }

        print(node.right,pfx+ (isRight ? "    ": "|   "), true);
        System.out.println("+---"+node.val);
        print(node.left,pfx+(isRight ? "|   ":"    "),false);

    }

    /**
     * height at most 1.44logn
     * @return
     */
    public int height (){
        if (root == null){
            return 0;
        }
        else {
            return root.h;
        }
    }

    public boolean isContain(Integer val){
        return search(root, val)==null?false:true;
    }

    /**
     * time complexity as O(logn)
     * @param i
     */
    private Node search(Node node,Integer i){
        if (i==null || node==null){
            return null;
        }
        Node temp=root;
        while(temp!=null){
            if (temp.val==i){
                return temp;
            }
        }
        return null;
    }

}

class TestAVLTree{
    public static void main (String args[]){
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