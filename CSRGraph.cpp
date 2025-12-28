#include "Jutil.h"
using namespace std;

const int N = 1e5;
const int M = N - 1;
int to[M << 1];
int nxt[M << 1];
int head[N];
int eCnt;
void addEdge(int u, int v) {
    to[eCnt] = v;
    nxt[eCnt] = head[u];
    head[u] = eCnt++;
}
void init(int n) {
    eCnt = 0;
    for (int i = 0; i < n; i++) {
        head[i] = -1;
    }
}

int main() {
    int n = 3;
    vector<vector<int>> edges = {{0, 1}, {1, 2}};
    int m = edges.size();
    init(n);
    for (int i = 0; i < m; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        addEdge(u, v);
        addEdge(v, u);
    }
    int u = 1;
    printf("Neighbors of %d: ", u);
    for (int i = head[u]; i != -1; i = nxt[i]) {
        int v = to[i];
        printf("%d,", v);
    }
    printf("\n");  // Neighbors of 1: 2,0,
    return 0;
}