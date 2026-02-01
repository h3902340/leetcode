#include "Jutil.h"
using namespace std;

struct RB {
    int v;
    int cnt;
    bool color;
    int p;
    int l;
    int r;
    bool leaf;
    int sz;
    RB& operator=(const RB& a) {
        v = a.v;
        cnt = a.cnt;
        color = a.color;
        p = a.p;
        l = a.l;
        r = a.r;
        leaf = a.leaf;
        sz = a.sz;
        return *this;
    }
};
const bool BLACK = 0;
const bool RED = 1;
const RB LEAF = {0, 0, BLACK, -1, -1, -1, true, 0};
const int N = 5e4;
const int M = N - 1;
class RBTree {
    const bool BLACK = 0;
    const bool RED = 1;
    const RB LEAF = {0, 0, BLACK, -1, -1, -1, true, 0};
    vector<RB> tree;
    int root;

   public:
    RBTree() { clear(); }
    RBTree& operator=(const RBTree& a) {
        tree = a.tree;
        root = a.root;
        return *this;
    }
    void clear() {
        tree.clear();
        tree.push_back(LEAF);
        root = 0;
    }
    void fix(int i) {
        while (i != root) {
            int p = tree[i].p;
            if (tree[p].color == BLACK) {
                break;
            }
            int g = tree[p].p;
            int l = tree[g].l;
            int r = tree[g].r;
            if (tree[l].color == RED && tree[r].color == RED) {
                tree[l].color = BLACK;
                tree[r].color = BLACK;
                tree[g].color = RED;
                i = g;
            } else {
                if (p == tree[g].l) {
                    if (i == tree[p].r) {
                        tree[p].r = tree[i].l;
                        tree[tree[i].l].p = p;
                        tree[p].sz =
                            1 + tree[tree[i].l].sz + tree[tree[p].l].sz;
                        tree[i].l = p;
                        tree[i].sz = 1 + tree[p].sz + tree[tree[i].r].sz;
                        tree[i].p = g;
                        tree[p].p = i;
                    } else {
                        i = p;
                    }
                    tree[g].color = RED;
                    tree[i].color = BLACK;
                    tree[g].l = tree[i].r;
                    tree[tree[i].r].p = g;
                    tree[g].sz = 1 + tree[tree[g].r].sz + tree[tree[i].r].sz;
                    tree[i].r = g;
                    tree[i].sz = 1 + tree[g].sz + tree[tree[i].l].sz;
                    int gp = tree[g].p;
                    tree[i].p = gp;
                    if (gp != -1) {
                        if (g == tree[gp].l) {
                            tree[gp].l = i;
                        } else {
                            tree[gp].r = i;
                        }
                    }
                    tree[g].p = i;
                } else {
                    if (i == tree[p].l) {
                        tree[p].l = tree[i].r;
                        tree[tree[i].r].p = p;
                        tree[p].sz =
                            1 + tree[tree[i].r].sz + tree[tree[p].r].sz;
                        tree[i].r = p;
                        tree[i].sz = 1 + tree[p].sz + tree[tree[i].l].sz;
                        tree[i].p = g;
                        tree[p].p = i;
                    } else {
                        i = p;
                    }
                    tree[g].color = RED;
                    tree[i].color = BLACK;
                    tree[g].r = tree[i].l;
                    tree[tree[i].l].p = g;
                    tree[g].sz = 1 + tree[tree[g].l].sz + tree[tree[i].l].sz;
                    tree[i].l = g;
                    tree[i].sz = 1 + tree[g].sz + tree[tree[i].r].sz;
                    int gp = tree[g].p;
                    tree[i].p = gp;
                    if (gp != -1) {
                        if (g == tree[gp].l) {
                            tree[gp].l = i;
                        } else {
                            tree[gp].r = i;
                        }
                    }
                    tree[g].p = i;
                }
                break;
            }
        }
        if (tree[i].p == -1) {
            root = i;
            tree[i].color = BLACK;
        }
    }
    void insert(int v) {
        int i = root;
        while (!tree[i].leaf) {
            tree[i].sz++;
            if (v == tree[i].v) {
                tree[i].cnt++;
                return;
            }
            if (v < tree[i].v) {
                i = tree[i].l;
            } else {
                i = tree[i].r;
            }
        }
        tree[i].v = v;
        tree.push_back(LEAF);
        tree[i].l = tree.size() - 1;
        tree[tree.size() - 1].p = i;
        tree.push_back(LEAF);
        tree[i].r = tree.size() - 1;
        tree[tree.size() - 1].p = i;
        tree[i].leaf = false;
        tree[i].sz = 1;
        tree[i].cnt = 1;
        tree[i].color = RED;
        fix(i);
    }
    void uniqueInsert(int v) {
        if (has(v)) {
            return;
        }
        insert(v);
    }
    bool has(int v) {
        int i = root;
        while (!tree[i].leaf) {
            if (v == tree[i].v) {
                return true;
            }
            if (v < tree[i].v) {
                i = tree[i].l;
            } else {
                i = tree[i].r;
            }
        }
        return false;
    }
    int getCnt(int v) {
        int i = root;
        while (!tree[i].leaf) {
            if (v == tree[i].v) {
                return tree[i].cnt;
            }
            if (v < tree[i].v) {
                i = tree[i].l;
            } else {
                i = tree[i].r;
            }
        }
        return 0;
    }
    int kth_element(int k) {
        int i = root;
        while (!tree[i].leaf) {
            int l = tree[i].l;
            int r = tree[i].r;
            if (k > tree[l].sz) {
                k -= tree[l].sz;
                if (k == 1) {
                    return tree[i].v;
                }
                k--;
                i = r;
            } else {
                i = l;
            }
        }
        return tree[tree[i].p].v;
    }
    void merge(RBTree& a) {
        for (int i = 0; i < a.tree.size(); i++) {
            if (a.tree[i].leaf) {
                continue;
            }
            insert(a.tree[i].v);
        }
    }
    void uniqueMerge(RBTree& a) {
        for (int i = 0; i < a.tree.size(); i++) {
            if (a.tree[i].leaf) {
                continue;
            }
            if (has(a.tree[i].v)) {
                continue;
            }
            insert(a.tree[i].v);
        }
    }
    int size() { return (tree.size() - 1) >> 1; }
};

int main() {
    vector<int> arr = {3, 1, 5, 6, 8, 11, 11, 8, 1, 10};
    int n = arr.size();
    RBTree rb;
    for (int i = 0; i < n; i++) {
        rb.insert(arr[i]);
    }
    printf("has(4):%d\n", rb.has(4));                  // has(4):0
    printf("has(5):%d\n", rb.has(5));                  // has(5):1
    printf("kth_element(3):%d\n", rb.kth_element(4));  // kth_element(4):5
    printf("getCnt(1):%d\n", rb.getCnt(1));            // getCnt(1):2
    return 0;
}