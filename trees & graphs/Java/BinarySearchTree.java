/**
 * @File BinarySearchTree.java
 * @Author Weilan Tao
 * @Date 2020-12-06
 * @Description This is the implementation for Binary Search Tree, Java version.
 * @Since version-1.2
 * @Copyright Copyright (c) 2020
 */


public class BinarySearchTree {
    private Node root;

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

        return node;
    }



    public void printTree(){
        if(root!=null){
            printTreeREC(root.right,"    ",true);
            System.out.println("+---"+root.value);
            printTreeREC(root.left,"    ",false);
        }

    }

    private void printTreeREC(Node node, String pfx,  boolean isRight){
        if(node==null){
            return;
        }

        printTreeREC(node.right,pfx+(isRight ? "    " : "|   "),true);
        System.out.println(pfx+"+---"+node.value);
        printTreeREC(node.left,pfx+(isRight ? "|   " : "    "),false);
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

    public Node getMin(Node node) {
        if (node == null) {
            return node;
        } else {
            while (node.left != null) {
                node = node.left;
            }
            return node;
        }
    }

    public Node remove(Node node, int value){
        if(node==null){
        }else{
            if (node.value==value){
                //have two child nodes
                if(node.left!=null && node.right!=null){
                    Node temp=getMin(node.right);
                    node.value=temp.value;
                    node.right=remove(node.right,temp.value);
                    temp=null;
                }
                else if(node.left!=null){
                    return node.left;
                }else if(node.right!=null){

                    return node.right;
                }
                else {
                    node=null;
                    return node;
                }

            }else if(node.value>value){
                node.left=remove(node.left, value);
            }else if (node.value<value){
                node.right=remove(node.right, value);
            }
        }
        return node;
    }

    public void remove(int value ){
        if(contains(value)) remove(root, value);
    }
}

class TestBST{
    public static void main(String [] args){
        BinarySearchTree bst = new BinarySearchTree();
        bst.insert(50);
        bst.insert(30);
        bst.insert(80);
        bst.insert(20);
        bst.insert(35);
        bst.insert(34);
        bst.insert(32);
        bst.insert(40);
        bst.insert(70);
        bst.insert(75);
        bst.insert(100);

        bst.printTree();
        bst.inOrder();
        System.out.println(bst.contains(4));

        bst.remove(70);
        bst.remove(4);

        bst.printTree();

        bst.remove(30);
        bst.printTree();


    }
}
