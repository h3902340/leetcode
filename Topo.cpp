#include "Jutil.h"
using namespace std;

const int N = 1e5;
class Topo {
   public:
    int deg[N];
    int nei[N];
    void init(int n) {
        for (int i = 0; i < n; i++) {
            nei[i] = 0;
        }
    }
    void addEdge(int u, int v) {
        deg[u]++;
        deg[v]++;
        nei[u] ^= v;
        nei[v] ^= u;
    }
};
Topo t;
int topo[N];

int main() {
    int n = 6;
    vector<vector<int>> edges = {{0, 1}, {0, 2}, {1, 3}, {1, 4}, {1, 5}};
    int m = edges.size();
    t.init(n);
    for (int i = 0; i < m; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        t.addEdge(u, v);
    }
    int j = 0;
    for (int i = 0; i < n; i++) {
        int a = i;
        while (t.deg[a] == 1) {
            topo[j++] = a;
            int p = t.nei[a];
            t.nei[p] ^= a;
            t.deg[p]--;
            t.deg[a] = 0;
            a = p;
        }
    }
    for (int i = 0; i < j; i++) {
        printf("%d,", topo[i]);
    }
    printf("\n");  // 2,0,3,4,1,
    return 0;
}