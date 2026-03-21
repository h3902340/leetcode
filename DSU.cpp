#include "Jutil.h"
using namespace std;

const int N = 1e5;
class DSU {
    int parent[N];
    int sz[N];

   public:
    void init(int n) {
        for (int i = 0; i < n; i++) {
            parent[i] = -1;
            sz[i] = 1;
        }
    }
    int find(int u) {
        int p = u;
        while (parent[p] != -1) {
            p = parent[p];
        }
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
            if (sz[b] < sz[a]) {
                parent[b] = a;
                sz[a] += sz[b];
            } else {
                parent[a] = b;
                sz[b] += sz[a];
            }
        }
    }
};

int main() {
    int n = 10;
    DSU dsu;
    vector<vector<int>> edges = {{3, 4}, {1, 0}, {2, 3}, {2, 1}};
    int m = edges.size();
    dsu.init(n);
    for (int i = 0; i < m; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        dsu.unite(u, v);
    }
    int a = dsu.find(0);
    int b = dsu.find(4);
    printf("a==b: %d\n", a == b);  // a==b: 1
    return 0;
}