#include "Jutil.h"
using namespace std;

const int N = 1e5;
int tree[N];
int sz;
void add(int i, int delta) {
    while (i < sz) {
        tree[i] += delta;
        i += i & -i;
    }
}
int query(int i) {
    int s = 0;
    while (i > 0) {
        s += tree[i];
        i -= i & -i;
    }
    return s;
}
void init(int n) {
    sz = n;
    for (int i = 1; i < sz; i++) {
        tree[i] = 0;
    }
}

int main() {
    int n = 10;
    // Fenwick Tree is 1-indexed
    vector<vector<int>> delta = {{0, 2}, {5, 1}, {7, -4}};
    init(n + 1);
    for (auto& d : delta) {
        add(d[0] + 1, d[1]);
    }
    for (int i = 1; i <= n; i++) {
        printf("%d,", query(i));
    }
    printf("\n");  // 2,2,2,2,2,3,3,-1,-1,-1,
    return 0;
}