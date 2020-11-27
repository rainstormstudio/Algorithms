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

struct Node {
    int key;
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;

    Node(int key) : key{key} {}
};

class BST {
    std::shared_ptr<Node> root;

    void print(std::ostream &out, std::shared_ptr<Node> node, int depth) {
        if (!node) return;
        for (int i = 0; i < depth; i ++) {
            out << "    ";
        }
        out << node->key << std::endl;
        print(out, node->left, depth + 1);
        print(out, node->right, depth + 1);
    }

    void inorder(std::ostream &out, std::shared_ptr<Node> node) {
        if (!node) return;
        inorder(out, node->left);
        out << node->key << " ";
        inorder(out, node->right);
    }

    std::shared_ptr<Node> search(std::shared_ptr<Node> node, int key) {
        if (!node) return nullptr;
        if (node->key == key) return node;
        if (node->key < key) {
            return search(node->right, key);
        } else {
            return search(node->left, key);
        }
        return node;
    }

    std::shared_ptr<Node> insert(std::shared_ptr<Node> node, int key) {
        if (!node) return std::make_shared<Node>(key);
        if (node->key == key) return node;
        if (node->key < key) {
            node->right = insert(node->right, key);
        } else {
            node->left = insert(node->left, key);
        }
        return node;
    }

    std::shared_ptr<Node> getMin(std::shared_ptr<Node> node) {
        std::shared_ptr<Node> min = node;
        while (min && min->left) {
            min = min->left;
        }
        return min;
    }

    std::shared_ptr<Node> remove(std::shared_ptr<Node> node, int key) {
        if (!node) return nullptr;
        if (node->key == key) {
            if (!node->left) {
                std::shared_ptr<Node> temp = node->right;
                node.reset();
                return temp;
            } else if (!node->right) {
                std::shared_ptr<Node> temp = node->left;
                node.reset();
                return temp;
            }
            std::shared_ptr<Node> temp = getMin(node->right);
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
        print(out, root, 0);
    }

    void inorder(std::ostream &out) {
        inorder(out, root);
    }

    std::shared_ptr<Node> search(int key) {
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