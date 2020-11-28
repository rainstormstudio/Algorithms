/**
 * @file red_black_tree.cc
 * @author Hongyu Ding 
 * @brief This is the program of Red-Black Tree class
 * @version 0.1
 * @date 2020-11-27
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include <iostream>
#include <memory>

struct Node;
using NodePtr = std::shared_ptr<Node>;

struct Node {
    enum Color {
        BLACK,
        RED
    };

    int key;
    NodePtr parent;
    NodePtr left;
    NodePtr right;
    Color color;

    Node() {
        key = 0;
        parent = nullptr;
        left = nullptr;
        right = nullptr;
        color = BLACK;
    }

    Node(int key, NodePtr parent, NodePtr nullnode, Color color)
        : key{key}, parent{parent}, left{nullnode}, right{nullnode}, color{color} {}
};

namespace RBTErrors {
    class RBTException {
    public:
        virtual std::string msg() = 0;
    };

    class KeyNotFoundException : public RBTException {
    public:
        std::string msg() override {
            return "ERROR: key not found!";
        }
    };
}

using namespace RBTErrors;

class RBT {
    NodePtr root;
    NodePtr TNULL;

    void print(std::ostream &out, NodePtr node, std::string pfx, bool isRight) {
        if (!node) return;
        print(out, node->right, pfx + (isRight ? "        " : "|       "), true);
        out << pfx + "+-------" << node->key << (node->color == Node::RED ? "(R)" : "(B)") << std::endl;
        print(out, node->left, pfx + (isRight ? "|       " : "        "), false);
    }

    void inorder(std::ostream &out, NodePtr node) {
        if (node == TNULL) return;
        inorder(out, node->left);
        out << node->key << " ";
        inorder(out, node->right);
    }

    void left_rotate(NodePtr x) {
        NodePtr y = x->right;
        x->right = y->left;
        if (y->left != TNULL) {
            y->left->parent = x;   
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            root = y;
        } else {
            if (x == x->parent->left) {
                x->parent->left = y;
            } else {
                x->parent->right = y;
            }
        }
        y->left = x;
        x->parent = y;
    }

    void right_rotate(NodePtr y) {
        NodePtr x = y->left;
        y->left = x->right;
        if (x->right != TNULL) {
            x->right->parent = y;
        }
        x->parent = y->parent;
        if (y->parent == nullptr) {
            root = x;
        } else {
            if (y == y->parent->right) {
                y->parent->right = x;
            } else {
                y->parent->left = x;
            }
        }
        x->right = y;
        y->parent = x;
    }

    void insert_fixup(NodePtr z) {
        NodePtr y;
        while (z->parent && z->parent->color == Node::RED && z->parent->parent) {
            if (z->parent == z->parent->parent->left) {
                y = z->parent->parent->right;
                if (y->color == Node::RED) {
                    z->parent->color = Node::BLACK;
                    y->color = Node::BLACK;
                    z->parent->parent->color = Node::RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->right) {
                        z = z->parent;
                        left_rotate(z);
                    }
                    z->parent->color = Node::BLACK;
                    z->parent->parent->color = Node::RED;
                    right_rotate(z->parent->parent);
                }
            } else {
                y = z->parent->parent->left;
                if (y->color == Node::RED) {
                    z->parent->color = Node::BLACK;
                    y->color = Node::BLACK;
                    z->parent->parent->color = Node::RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->left) {
                        z = z->parent;
                        right_rotate(z);
                    }
                    z->parent->color = Node::BLACK;
                    z->parent->parent->color = Node::RED;
                    left_rotate(z->parent->parent);
                }
            }
        }
        root->color = Node::BLACK;
    }

    void transplant(NodePtr x, NodePtr y) {
        if (x->parent == nullptr) {
            root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        y->parent = x->parent;
    }

    NodePtr findMin(NodePtr node) {
        while (node->left != TNULL) {
            node = node->left;
        }
        return node;
    }

    void remove_fixup(NodePtr x) {
        NodePtr w;
        while (x != root && x->color == Node::BLACK) {
            if (x == x->parent->left) {
                w = x->parent->right;
                if (w->color == Node::RED) {
                    w->color = Node::BLACK;
                    x->parent->color = Node::RED;
                    left_rotate(x->parent);
                    w = x->parent->right;
                }
                if (w->left->color == Node::BLACK && w->right->color == Node::BLACK) {
                    w->color = Node::RED;
                    x = x->parent;
                } else {
                    if (w->right->color == Node::BLACK) {
                        w->left->color = Node::BLACK;
                        w->color = Node::RED;
                        right_rotate(w);
                        w = x->parent->right;
                    }
                    w->color = x->parent->color;
                    x->parent->color = Node::BLACK;
                    w->right->color = Node::BLACK;
                    left_rotate(x->parent);
                    x = root;
                }
            } else {
                w = x->parent->left;
                if (w->color == Node::RED) {
                    w->color = Node::BLACK;
                    x->parent->color = Node::RED;
                    right_rotate(x->parent);
                    w = x->parent->left;
                }
                if (w->right->color == Node::BLACK && w->left->color == Node::BLACK) {
                    w->color = Node::RED;
                    x = x->parent;
                } else {
                    if (w->left->color == Node::BLACK) {
                        w->right->color = Node::BLACK;
                        w->color = Node::RED;
                        left_rotate(w);
                        w = x->parent->left;
                    }
                    w->color = x->parent->color;
                    x->parent->color = Node::BLACK;
                    w->left->color = Node::BLACK;
                    right_rotate(x->parent);
                    x = root;
                }
            }
        }
    }

public:
    RBT() {
        TNULL = std::make_shared<Node>();
        root = TNULL;
    }

    void print(std::ostream &out) {
        if (!root) return;
        print(out, root->right, "    ", true);
        out << "+---" << root->key << (root->color == Node::RED ? "(R)" : "(B)") << std::endl;
        print(out, root->left, "    ", false);
    }

    void inorder(std::ostream &out) {
        inorder(out, root);
    }

    void insert(int key) {
        NodePtr z = std::make_shared<Node>(key, nullptr, TNULL, Node::RED);
        NodePtr y = nullptr;
        NodePtr x = root;
        while (x != TNULL) {
            y = x;
            if (z->key < x->key) {
                x = x->left;
            } else {
                x = x->right;
            }
        }
        z->parent = y;
        if (!y) {
            root = z;
        } else {
            if (z->key < y->key) {
                y->left = z;
            } else {
                y->right = z;
            }
        }
        insert_fixup(z);
    }

    NodePtr search(int key) {
        NodePtr node = root;
        while (node != TNULL) {
            if (node->key == key) {
                return node;
            }
            if (node->key < key) {
                node = node->right;
            } else {
                node = node->left;
            }
        }
        throw KeyNotFoundException();
        return nullptr;
    }

    void remove(int key) {
        NodePtr node = root;
        NodePtr z = TNULL;
        while (node != TNULL) {
            if (node->key == key) {
                z = node;
            }
            if (node->key <= key) {
                node = node->right;
            } else {
                node = node->left;
            }
        }
        if (z == TNULL) {
            throw KeyNotFoundException();
            return;
        }

        NodePtr x, y = z;
        Node::Color y_color = y->color;
        if (z->left == TNULL) {
            x = z->right;
            transplant(z, z->right);
        } else if (z->right == TNULL) {
            x = z->left;
            transplant(z, z->left);
        } else {
            y = findMin(z->right);
            y_color = y->color;
            x = y->right;
            if (y->parent == z) {
                x->parent = y;
            } else {
                transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }
        z.reset();
        if (y_color == Node::BLACK) {
            remove_fixup(x);
        }
    }
};

int main() {
    RBT tree = RBT();
    char command;
    while (std::cin >> command) {
        try {
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
        } catch (RBTException &e) {
            std::cout << e.msg() << std::endl;
        }
    }
    return 0;
}