/**
 * @file tree.cc
 * @author Hongyu Ding
 * @brief This is a normal tree class 
 * @version 0.1
 * @date 2020-11-20
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include <iostream>
#include <string>
#include <vector>
#include <memory>

class Node {
    std::string data;
    std::vector<std::shared_ptr<Node>> children;
public:
    Node(std::istream &in) {
        std::string line;
        std::getline(in, line);
        data = line;
        std::getline(in, line);
        int numChildren = std::stoi(line);
        for (int i = 0; i < numChildren; i ++) {
            children.emplace_back(std::make_shared<Node>(in));
        }
    }

    void output(std::ostream &out, int depth) {
        for (int i = 0; i < depth; i ++) {
            out << "    ";
        }
        out << data << "\n";
        for (auto child : children) {
            child->output(out, depth + 1);
        }
    }
};

class Tree {
    std::shared_ptr<Node> root;
public:
    Tree(std::istream &in) {
        root = std::make_shared<Node>(in);
    }

    void output(std::ostream &out) {
        root->output(out, 0);
    }
};

int main() {
    Tree t = Tree(std::cin);
    t.output(std::cout);
    return 0;
}
