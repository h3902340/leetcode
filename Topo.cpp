#include "Jutil.h"
using namespace std;

const int N = 1e5;
int deg[N];
int nei[N];
int topo[N];
void init(int n) {
    for (int i = 0; i < n; i++) {
        nei[i] = 0;
    }
}

int main() {
    int n = 6;
    vector<vector<int>> edges = {{0, 1}, {0, 2}, {1, 3}, {1, 4}, {1, 5}};
    int m = edges.size();
    init(n);
    for (int i = 0; i < m; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        deg[u]++;
        deg[v]++;
        nei[u] ^= v;
        nei[v] ^= u;
    }
    int j = 0;
    for (int i = 0; i < n; i++) {
        int a = i;
        while (deg[a] == 1) {
            topo[j++] = a;
            int p = nei[a];
            nei[p] ^= a;
            deg[p]--;
            deg[a] = 0;
            a = p;
        }
    }
    for (int i = 0; i < j; i++) {
        printf("%d,", topo[i]);
    }
    printf("\n");  // 2,0,3,4,1,
    return 0;
}