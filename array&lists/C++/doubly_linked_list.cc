/**
 * @file doubly_linked_list.cc
 * @author Hongyu Ding
 * @brief This is the implementation of doubly linked list
 * @version 0.1
 * @date 2020-10-24
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include <iostream>

template <typename T>
class Node {
public:
    T data;
    Node<T> *prev, *next;
    Node() : data{0}, prev{nullptr}, next{nullptr} {}
    Node(T data, Node<T> *prev, Node<T> *next)
        : data{data}, prev{prev}, next{next} {}
};

template <typename T>
class DLinkedList {
    Node<T> *head;
    Node<T> *tail;
    int size;

public:

    DLinkedList() : head{nullptr}, tail{nullptr}, size{0} {}

    void clear() {
        Node<T> *node = head;
        while (node != nullptr) {
            Node<T> *next = node->next;
            delete node;
            node = next;
        }
        head = tail = nullptr;
        size = 0;
    }

    int getSize() const { return size; }

    bool isEmpty() const { return size == 0; }

    void add(T val) {
        addLast(val);
    }

    void addFirst(T val) {
        if (isEmpty()) {
            head = tail = new Node<T>(val, nullptr, nullptr);
        } else {
            head.prev = new Node<T>(val, nullptr, head);
            head = head->prev;
        }
        size ++;
    }

    void addLast(T val) {
        if (isEmpty()) {
            head = tail = new Node<T>(val, nullptr, nullptr);
        } else {
            tail->next = new Node<T>(val, tail, nullptr);
            tail = tail->next;
        }
        size ++;
    }

    T front() {
        if (isEmpty()) return 0;
        return head->data;
    }

    T end() {
        if (isEmpty()) return 0;
        return tail->data;
    }

    T removeFront() {
        if (isEmpty()) return 0;
        T data = head->data;
        Node<T> *temp = head;
        head = head->next;
        delete temp;
        size --;
        if (isEmpty()) {
            tail = nullptr;
        } else {
            head->prev = nullptr;
        }
        return data;
    }

    T removeEnd() {
        if (isEmpty()) return 0;
        T data = tail.data;
        Node<T> *temp = tail;
        tail = tail->prev;
        delete temp;
        size --;
        if (isEmpty()) {
            head = nullptr;
        } else {
            tail->next = nullptr;
        }
        return data;
    }

    T remove(Node<T> *node) {
        if (!node->prev) return removeFront();
        if (!node->next) return removeEnd();
        node->next->prev = node->prev;
        node->prev->next = node->next;
        T data = node->data;
        delete node;
        size --;
        return data;
    }

    T removeAt(int index) {
        Node<T> *node = nullptr;
        if (index < size / 2) {
            node = head;
            for (int i = 0; i < index; i ++) {
                node = node->next;
            }
        } else {
            node = tail;
            for (int i = size - 1; i > index; i --) {
                node = node->prev;
            }
        }
        return remove(node);
    }

    int indexOf(T val) {
        int index = 0;
        Node<T> *node = head;
        for (node = head; node != nullptr; node = node->next) {
            if (val == node->data) {
                return index;
            }
            index ++;
        }
        return -1;
    }

    T operator[](int index) {
        Node<T> *node = nullptr;
        if (index < size / 2) {
            node = head;
            for (int i = 0; i < index; i ++) {
                node = node->next;
            }
        } else {
            node = tail;
            for (int i = size - 1; i > index; i --) {
                node = node->prev;
            }
        }
        return node->data;
    }

    bool contains(T val) {
        return indexOf(val) != -1;
    }

    void print(std::ostream &out) {
        out << "[" << head->data;
        Node<T> *node = head;
        node = node->next;
        while (node) {
            out << ", " << node->data;
            node = node->next;
        }
        out << "]";
    }
};

int main() {
    DLinkedList<int> list;
    list.add(1);
    list.add(5);
    list.add(8);
    list.print(std::cout);
    std::cout << std::endl << "list[2] = " << list[2] << std::endl;
    std::cout << "front = " << list.front() << std::endl;
    std::cout << "end = " << list.end() << std::endl;
    return 0;
}