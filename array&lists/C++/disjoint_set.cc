/**
 * @file disjoint_set.cc
 * @author Hongyu Ding
 * @brief This is an implementation of the disjoint set (optimized)
 * @version 0.1
 * @date 2020-10-25
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include <iostream>
#include <vector>

using List = std::vector<int>;

class DisjointSet {
    List parent;    // parent of i, if parent[i] == i then i is a root node
    List rank;
    int numSets;    // number of sets

public:
    DisjointSet(int max_size) {
        parent = List(max_size);
        rank = List(max_size);
        numSets = max_size;
        for (int i = 0; i < max_size; i ++) {
            parent[i] = i; rank[i] = 0;
        }
    }

    int find(int x) {
        return (x == parent[x] ? x : (parent[x] = find(parent[x])));
    }

    void unify(int a, int b) {
        int root1 = find(a);
        int root2 = find(b);
        if (root1 == root2) return;
        if (rank[root1] > rank[root2]) {
            parent[root2] = root1;
        } else {
            parent[root1] = root2;
            if (rank[root1] == rank[root2]) {
                rank[root2] ++;
            }
        }
        numSets --;
    }

    bool isSameSet(int a, int b) {
        return find(a) == find(b);
    }

    int getNumSets() const { return numSets; }
};

int main() {
    int n;
    std::cin >> n;
    DisjointSet sets(n);
    char ch;
    bool loop = true;
    while(loop) {
        std::cin >> ch;
        switch (ch) {
            case 'F': {
                int val;
                std::cin >> val;
                std::cout << sets.find(val) << std::endl;
                break;
            }
            case 'U': {
                int a, b;
                std::cin >> a >> b;
                sets.unify(a, b);
                std::cout << "sets unified" << std::endl;
                break;
            }
            case 'S': {
                int a, b;
                std::cin >> a >> b;
                bool flag = sets.isSameSet(a, b);
                if (flag) {
                    std::cout << "they are in the same set" << std::endl;
                } else {
                    std::cout << "they are not in the same set" << std::endl;
                }
                break;
            }
            case 'N': {
                std::cout << "number of sets: " << sets.getNumSets() << std::endl;
                break;
            }
            case 'Q': {
                loop = false;
                break;
            }
            default: {
                std::cout << "please start with F/U/S/N" << std::endl;
                std::cout << "    F x : find x" << std::endl;
                std::cout << "    U a b : unify a and b's sets" << std::endl;
                std::cout << "    S a b : check if a and b are in the same set" << std::endl;
                std::cout << "    N : get number of sets" << std::endl;
                std::cout << "    Q : quit" << std::endl;
                break;
            }
        }
    }
    return 0;
}
