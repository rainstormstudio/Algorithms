/**
 * @File TQueue.java
 * @Author Weilan Tao
 * @Date 2020-12-02
 * @Description This is the implementation for linked list based Queue, Java version.
 * @Since version-1.1
 * @Copyright Copyright (c) 2020
 */


public class TQueue<T> {

    private Node<T> head;
    private Node<T> tail;
    private int size=0;

    private class Node<T>{
        private T data;
        private Node<T> next=null;

        public Node (T data){
            this.data =data;
        }
    }

    public int getSize() {
        return size;
    }

    public TQueue(){
        head=new Node<T>(null);
        tail=this.head;
        size=0;
        tail.next=null;
    }

    /**
     * Time complexity as O(1)
     */
    public void enQueue(T t){
        Node<T> node = new Node<>(t);
        if(isEmpty()){
            head=node;
            tail=node;
            head.next=null;
            tail.next=null;
        }else{
            tail.next=node;
            node.next=null;
            tail=node;
        }
        size++;
    }

    /**
     * Time complexity as O(1)
     */
    public void deQueue() throws Exception {
        if(isEmpty()){
            throw new Exception();
        }else{
            size--;
            head=head.next;
        }
    }

    public void deleteQueue(){
        while(head!=tail){
            try {
                deQueue();
            }catch (Exception e) {
                System.out.println("Can not do deQueue()");
            }
        }
        try {
            deQueue();
        }catch (Exception e) {
            System.out.println("Can not do deQueue()");
        }

    }

    public boolean isEmpty(){
        return this.size==0? true:false;
    }

    public void printQueue() {
        if(isEmpty()){
            System.out.println("The Queue is empty.");
        }
        for(Node<T> temp=head; temp!=null; temp=temp.next){
            System.out.print(temp.data);
        }
        System.out.println(" ");

    }

}

class testTQueue{
    public static void main (String args[]){
        TQueue<Character> tQueue=new TQueue<>();
        tQueue.enQueue('H');
        tQueue.enQueue('e');
        tQueue.enQueue('l');
        tQueue.enQueue('l');
        tQueue.enQueue('o');
        tQueue.enQueue(' ');
        tQueue.enQueue('W');
        tQueue.enQueue('o');
        tQueue.enQueue('r');
        tQueue.enQueue('l');
        tQueue.enQueue('d');
        tQueue.printQueue();
        System.out.println(tQueue.getSize());

        try {
            tQueue.deQueue();
        } catch (Exception e) {
            System.out.println("Can not do deQueue()");
        }
        System.out.println(tQueue.getSize());

        tQueue.printQueue();

        tQueue.deleteQueue();
        tQueue.printQueue();
        try {
            tQueue.deQueue();
        } catch (Exception e) {
            System.out.println("Can not do deQueue()");
        }
        System.out.println(tQueue.getSize());


        tQueue.enQueue('H');
        tQueue.enQueue('i');
        tQueue.enQueue('i');
        tQueue.enQueue('i');
        tQueue.printQueue();
        System.out.println(tQueue.getSize());

    }
}
