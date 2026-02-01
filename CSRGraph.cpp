#include "Jutil.h"
using namespace std;

const int N = 1e5;
const int M = N - 1;
class CSRGraph {
    int eCnt;

   public:
    int to[M << 1];
    int nxt[M << 1];
    int head[N];
    CSRGraph(int n) {
        eCnt = 0;
        for (int i = 0; i < n; i++) {
            head[i] = -1;
        }
    }
    void addEdge(int u, int v) {
        to[eCnt] = v;
        nxt[eCnt] = head[u];
        head[u] = eCnt++;
    }
};

int main() {
    int n = 3;
    vector<vector<int>> edges = {{0, 1}, {1, 2}};
    int m = edges.size();
    CSRGraph graph(n);
    for (int i = 0; i < m; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        graph.addEdge(u, v);
        graph.addEdge(v, u);
    }
    int u = 1;
    printf("Neighbors of %d: ", u);
    for (int i = graph.head[u]; i != -1; i = graph.nxt[i]) {
        int v = graph.to[i];
        printf("%d,", v);
    }
    printf("\n");  // Neighbors of 1: 2,0,
    return 0;
}