/**
 * @File Doubly LinkedList
 * @Author Weilan Tao
 * @Date 2020-10-31
 * @Description This is the implementation for DoublyLinkedList, java version.
 * @Since version-1.0
 * @Copyright Copyright (c) 2020
 */


public class DoublyLinkedList<T> {

    private static int length = 0;
    private Node<T> head;//the head node will always be empty
    private Node<T> tail;

    /**
     * Constructor
     */
    public DoublyLinkedList() {
        this.head = new Node<T>();
        this.tail = new Node<T>();
        this.length = 0;

    }

    public boolean isEmpty() {
        return length == 0;
    }

    public int getLength() {
        return length;
    }

    public void add(T val) {

        if (isEmpty()) {
            Node<T> node = new Node<T>(val, head, null);
            head.next = node;
            tail = node;
        } else {
            Node<T> temp = this.tail;
            Node<T> node = new Node<T>(val, temp, null);
            this.tail = node;
            temp.next = node;
        }
        length++;

    }

    /**
     * Add a node after a certain value
     *
     * @param val
     * @param key
     */
    public void insertAfter(T val, T key) {
        if (key == null) {
            throw new NullPointerException("the key value can't be empty");
        } else {
            int index = indexOf(key);
            if (index <= length - 2) {
                length++;
                Node<T> temp;
                temp = head.next;
                for (int i = 0; i < index; i++) {
                    temp = temp.next;
                }
                Node<T> node = new Node<T>(val, temp, temp.next);
                Node<T> tn = temp.next;
                temp.next = node;
                tn.pervious = node;
            } else if (index < DoublyLinkedList.length) {
                add(val);
            }
        }
    }

    public void transversalFromHead() {
        if (isEmpty()) System.out.println("Empty Doubly LinkedList. Cannot print.");
        else {
            Node<T> temp = head.next;
            while (temp.next != null) {
                System.out.print(temp.data + " -> ");
                temp = temp.next;
            }
            System.out.println(temp.data);
        }

    }

    public boolean contains(T val) {
        return indexOf(val) != -1;
    }

    public int indexOf(T val) {
        int index = -1;
        int i = 0;
        Node<T> temp;
        for (temp = head.next; temp.next != null; temp = temp.next) {
            if (val == temp.data) {
                index = i;
                return index;
            }
            i++;
        }
        if (val == temp.data) {
            index = i;
        }
        return index;
    }

    public void removeAt(int index) {
        Node<T> temp = new Node<T>();
        temp = head.next;
        for (int i = 0; i < index; i++) {
            temp = temp.next;
        }
        temp.pervious.next = temp.next;
        temp.data = null;
        temp.pervious = null;
        temp.next = null;
        length--;
    }

    /**
     * Delete the DLL
     */
    public void clean() {
        if (isEmpty()) System.out.println("Empty Doubly LikedList. Cannot clean.");
        else {
            Node<T> temp = head;
            Node<T> trans;
            while (temp.next != null) {
                trans = temp;
                temp = temp.next;
                trans.data = null;
                trans.pervious = null;
                trans.next = null;
                length--;
            }
            this.head.next = null;
            this.tail = this.head;
            System.out.println("Cleaning finished");
        }
    }

    /**
     * Inner Class Node
     *
     * @param <T>
     */
    private class Node<T> {
        private T data;
        private Node<T> next = null;
        private Node<T> pervious = null;

        public Node(T data, Node<T> pervious, Node<T> next) {
            this.data = data;
            this.next = next;
            this.pervious = pervious;
        }

        public Node() {
            this.data = null;
            this.next = null;
            this.pervious = null;
        }

    }
}

class testDoublyLinkedList {
    public static void main(String[] args) {
        DoublyLinkedList<Integer> list = new DoublyLinkedList<Integer>();
        System.out.println("Test..isEmpty().." + list.isEmpty());
        list.add(1);
        System.out.println("Test..isEmpty().." + list.isEmpty());
        list.add(3);
        list.add(5);
        list.add(7);
        list.add(9);
        System.out.println("Test..indexOf(),9.." + list.indexOf(9));
        System.out.println("Test..contains(),3.." + list.contains(3));
        System.out.println("Test..contains(),6.." + list.contains(6));
        System.out.println("The length is " + list.getLength());
        list.transversalFromHead();
        System.out.println("Test..removeAt(),0,1");
        list.removeAt(1);
        list.removeAt(0);
        list.transversalFromHead();
        list.insertAfter(4, 7);
        list.transversalFromHead();
        list.insertAfter(10, 9);
        list.transversalFromHead();
        System.out.println("The length is " + list.getLength());
        System.out.println("Test..clean()");
        list.clean();
        System.out.println("The length is " + list.getLength());
        System.out.println("Test..isEmpty()  " + list.isEmpty());

    }
}



