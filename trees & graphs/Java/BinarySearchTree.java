/**
 * @File BinarySearchTree.java
 * @Author Weilan Tao
 * @Date 2020-12-03
 * @Description This is the implementation for Binary Search Tree, Java version.
 * @Since version-1.1
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
        inOrderRec(root);
        System.out.println(" ");
    }
    private void inOrderRec(Node node){
        if (node!=null){
            inOrderRec(node.left);
            System.out.print(node.value+" ");
            inOrderRec(node.right);
        }
    }
    private void preOrder(Node node){

    }
    private void levelOrder(Node node){

    }


    public boolean contains(int val){
        return  searchRec(root, val)!=null;
    }

    private Node searchRec(Node node, int val){
        if(node==null){
            return null;
        }else{
            if(node.value==val){
                return node;
            }
            else if(node.value>val){
                return searchRec(node.left,val);
            }else if(node.value<val){
                return searchRec(node.right,val);
            }
            return node;
        }
    }

    public Node getMin(Node node){
        return null;
    }

    public Node remove(Node node, int value){
        if(node==null){
            return null;
        }

        if (node.value==value){
            //have two child nodes
            if(node.left!=null && node.right!=null){



            }
            //have one child node
            else if(node.left!=null){
                Node temp= getMin(node);
                temp.

            }else if(node.right!=null){

            }
            //have no child node
            else {
                node=null;
                return node;
            }


        }else if(node.value>value){
            return null;
        }else if (node.value<value){
            return null;
        }


    }

    public void remove(int value ){
        if(contains(value)) remove(root, value);
    }
}

class TestBST{
    public static void main(String [] args){
        BinarySearchTree bst = new BinarySearchTree();
        bst.insert(6);
        bst.insert(4);
        bst.insert(8);
        bst.insert(3);
        bst.insert(5);
        bst.insert(7);
        bst.insert(9);
//        bst.printTree();
        bst.inOrder();
        System.out.println(bst.contains(4));

        bst.remove(9);
        bst.remove(4);

    }
}
