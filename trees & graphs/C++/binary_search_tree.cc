/**
 * @file binary_search_tree.cc
 * @author Hongyu Ding 
 * @brief This is an example of Binary Search Tree
 * @version 0.1
 * @date 2020-11-27
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include <iostream>
#include <memory>
#include <vector>
#include <string>

struct Node;
using NodePtr = std::shared_ptr<Node>;

struct Node {
    int key;
    NodePtr left;
    NodePtr right;

    Node(int key) : key{key} {}
};

class BST {
    NodePtr root;

    void print(std::ostream &out, NodePtr node, std::string pfx, bool isRight) {
        if (!node) return;
        print(out, node->right, pfx + (isRight ? "    " : "|   "), true);
        out << pfx + "+---" << node->key << std::endl;
        print(out, node->left, pfx + (isRight ? "|   " : "    "), false);
    }

    void inorder(std::ostream &out, NodePtr node) {
        if (!node) return;
        inorder(out, node->left);
        out << node->key << " ";
        inorder(out, node->right);
    }

    NodePtr search(NodePtr node, int key) {
        if (!node) return nullptr;
        if (node->key == key) return node;
        if (node->key < key) {
            return search(node->right, key);
        } else {
            return search(node->left, key);
        }
        return node;
    }

    NodePtr insert(NodePtr node, int key) {
        if (!node) return std::make_shared<Node>(key);
        if (node->key == key) return node;
        if (node->key < key) {
            node->right = insert(node->right, key);
        } else {
            node->left = insert(node->left, key);
        }
        return node;
    }

    NodePtr getMin(NodePtr node) {
        NodePtr min = node;
        while (min && min->left) {
            min = min->left;
        }
        return min;
    }

    NodePtr remove(NodePtr node, int key) {
        if (!node) return nullptr;
        if (node->key == key) {
            if (!node->left) {
                NodePtr temp = node->right;
                node.reset();
                return temp;
            } else if (!node->right) {
                NodePtr temp = node->left;
                node.reset();
                return temp;
            }
            NodePtr temp = getMin(node->right);
            node->key = temp->key;
            node->right = remove(node->right, temp->key);
        } else if (node->key < key) {
            node->right = remove(node->right, key);
        } else if (node->key > key) {
            node->left = remove(node->left, key);
        }
        return node;
    }

public:
    BST() : root{nullptr} {}
    BST(std::vector<int> &ary) {
        for (auto val : ary) {
            insert(val);
        }
    }

    void print(std::ostream &out) {
        if (!root) return;
        print(out, root->right, "    ", true);
        out << "+---" << root->key << std::endl;
        print(out, root->left, "    ", false);
    }

    void inorder(std::ostream &out) {
        inorder(out, root);
    }

    NodePtr search(int key) {
        return search(root, key);
    }

    void insert(int key) {
        if (root) {
            insert(root, key);
        } else {
            root = insert(root, key);
        }
    }

    void remove(int key) {
        remove(root, key);
    }
};

int main() {
    BST tree = BST();
    char command;
    while (std::cin >> command) {
        switch (command) {
            case 'a': {
                int val;
                std::cin >> val;
                tree.insert(val);
                break;
            }
            case 'd': {
                int val;
                std::cin >> val;
                tree.remove(val);
                break;
            }
            case 'p': {
                tree.print(std::cout);
                break;
            }
            case 's': {
                int val;
                std::cin >> val;
                std::cout << tree.search(val)->key << std::endl;
                break;
            }
            case 'i': {
                tree.inorder(std::cout);
                std::cout << std::endl;
            }
        }
    }
    return 0;
}