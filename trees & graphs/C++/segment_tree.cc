/**
 * @file segment_tree.cc
 * @author Hongyu Ding
 * @brief This is the code for segment tree (segment sum)
 * @version 1.0
 * @date 2020-10-23
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include <iostream>
#include <vector>

struct SegmentTree {
    int l;      // left boundary
    int r;      // right boundary
    int sum;    // sum of the interval [l, r]
    int tag;    // downtag optimization
};

void buildTree(std::vector<SegmentTree>& st, int index, int l, int r) {
    st[index].l = l;
    st[index].r = r;
    st[index].sum = 0;
    st[index].tag = 0;
    if (l == r) return;
    buildTree(st, index * 2 + 1, l, (l + r) / 2);
    buildTree(st, index * 2 + 2, (l + r) / 2 + 1, r);
}

/**
 * @brief build builds the segment tree
 * O(n log n)
 * 
 * @param st 
 * @param n 
 */
void build(std::vector<SegmentTree> &st, int n) {
    st = std::vector<SegmentTree>(n * n);
    buildTree(st, 0, 0, n - 1);
}

void downtag(std::vector<SegmentTree> &st, int index) {
    st[index * 2 + 1].sum = st[index * 2 + 1].sum + st[index].tag * (st[index * 2 + 1].r - st[index * 2 + 1].l + 1);
    st[index * 2 + 2].sum = st[index * 2 + 2].sum + st[index].tag * (st[index * 2 + 2].r - st[index * 2 + 2].l + 1);
    st[index * 2 + 1].tag = st[index].tag;
    st[index * 2 + 2].tag = st[index].tag;
    st[index].tag = 0;
}

/**
 * @brief modifyTree adds val to all values in interval [l, r]
 * O(n log n)
 * 
 * @param st 
 * @param index 
 * @param l 
 * @param r 
 * @param val 
 */
void modifyTree(std::vector<SegmentTree> &st, int index, int l, int r, int val) {
    int mid = (st[index].l + st[index].r) / 2;
    if (st[index].tag) downtag(st, index);
    if (l <= st[index].l && r >= st[index].r) {
        st[index].sum = st[index].sum + val * (st[index].r - st[index].l + 1);
        st[index].tag = val;
        return;
    }
    if (l <= mid) modifyTree(st, index * 2 + 1, l, r, val);
    if (r > mid) modifyTree(st, index * 2 + 2, l, r, val);
    st[index].sum = st[index * 2 + 1].sum + st[index * 2 + 2].sum;
}

/**
 * @brief ask returns the sum of the value in interval [l, r]
 * O(n log n)
 * 
 * @param st segment tree
 * @param index 
 * @param l 
 * @param r 
 * @return int 
 */
int ask(std::vector<SegmentTree> &st, int index, int l, int r) {
    int mid = (st[index].l + st[index].r) / 2;
    int ans = 0;
    if (st[index].tag) downtag(st, index);
    if (l <= st[index].l && r >= st[index].r) return st[index].sum;
    if (l <= mid) ans += ask(st, index * 2 + 1, l, r);
    if (r > mid) ans += ask(st, index * 2 + 2, l, r);
    return ans;
}

/**
 * @brief modify adds val to st at index i
 * 
 * @param st 
 * @param i 
 * @param val 
 */
void modify(std::vector<SegmentTree> &st, int i, int val) {
    modifyTree(st, 0, i, i, val);
}

int main() {
    int n;
    std::cin >> n;
    std::vector<SegmentTree> st;

    build(st, n); // tree initialization

    for (int i = 0; i < n; i ++) {
        int val;
        std::cin >> val;
        modify(st, i, val);
    }

    int m;
    std::cin >> m;
    for (int i = 0; i < m; i ++) {
        char ch;
        std::cin >> ch;
        switch (ch) {
            case 'V': {
                int index, val;
                std::cin >> index >> val;
                modify(st, index, val);
                break;
            }
            case 'A': {
                int l, r, val;
                std::cin >> l >> r >> val;
                modifyTree(st, 0, l, r, val);
                break;
            }
            case 'S': {
                int l, r;
                std::cin >> l >> r;
                std::cout << ask(st, 0, l, r) << std::endl;
                break;
            }
            default: {
                std::cout << "Please enter A l r val for adding interval[l, r] with val" << std::endl;
                std::cout << "    or enter V i val for adding the value at index i to val" << std::endl;
                std::cout << "    or enter S l r for getting the sum of the interval[l, r]" << std::endl;
                break;
            }
        }
    }

    return 0;
}
