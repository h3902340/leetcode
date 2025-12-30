#include "Jutil.h"
using namespace std;

const int N = 1e5;
int parent[N];
int find(int u) {
    int p = u;
    while (parent[p] != -1) {
        p = parent[p];
    }
    // collapsing
    while (parent[u] != -1) {
        int tmp = parent[u];
        parent[u] = p;
        u = tmp;
    }
    return p;
}
void unite(int u, int v) {
    int a = find(u);
    int b = find(v);
    if (b != a) {
        parent[b] = a;
    }
}
void init(int n) {
    for (int i = 0; i < n; i++) {
        parent[i] = -1;
    }
}

int main() {
    int n = 10;
    vector<vector<int>> edges = {{3, 4}, {1, 0}, {2, 3}, {2, 1}};
    int m = edges.size();
    init(n);
    for (int i = 0; i < m; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        unite(u, v);
    }
    int a = find(0);
    int b = find(4);
    printf("a==b: %d\n", a == b);  // a==b: 1
    return 0;
}