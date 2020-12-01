/**
 * @File TQueue.java
 * @Author Weilan Tao
 * @Date 2020-12-02
 * @Description This is the implementation for linked list based Queue, Java version.
 * @Since version-1.0
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

        public T getData() {
            return data;
        }

        public void setData(T data) {
            this.data = data;
        }
    }

    public TQueue(){
        this.head=new Node<T>(null);
        this.tail=this.head;
        this.size=0;
        head.next=null;
    }

    /**
     * Time complexity as O(1)
     */
    public void push(T t){
        if(isEmpty()){
            head.setData(t);
        }else{
            //TODO fix to reduce the Time complexity
            Node<T> temp = head;
            while(temp.next!=null){
                temp=temp.next;
            }
            Node<T> node = new Node<>(t);
            temp.next=node;
            this.tail=node;
        }
        size++;
    }

    /**
     * Time complexity as O(1)
     */
    public void pop(){

    }

    public void peek(){

    }

    public void deleteQueue(){

    }

    public boolean isEmpty(){
        return this.size==0? true:false;
    }

    public void printQueue(){
        for(Node<T> temp=head; temp!=null; temp=temp.next){
            System.out.print(temp.data);
        }
    }

}

class testTQueue{
    public static void main (String args[]){
        TQueue<Character> tQueue=new TQueue<>();
        tQueue.push('H');
        tQueue.push('e');
        tQueue.push('l');
        tQueue.push('l');
        tQueue.push('o');
        tQueue.push(' ');
        tQueue.push('W');
        tQueue.push('o');
        tQueue.push('r');
        tQueue.push('l');
        tQueue.push('d');
        tQueue.printQueue();


    }
}
