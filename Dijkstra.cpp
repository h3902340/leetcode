#include "Jutil.h"
using namespace std;

struct Data {
    int v;
    int w;
};

// CSR Graph
const int N = 5e4;
const int M = 1e5;
Data to[M << 1];
int nxt[M << 1];
int head[N];
int eCnt;
void addEdge(int u, int v, int w) {
    to[eCnt] = {v, w};
    nxt[eCnt] = head[u];
    head[u] = eCnt++;
}
void init(int n) {
    eCnt = 0;
    for (int i = 0; i < n; i++) {
        head[i] = -1;
    }
}

// Dijkstra
int dis[N];
bool vis[N];
auto cmp = [](Data& a, Data& b) { return a.w > b.w; };
void dijkstra(int u, int n) {
    priority_queue<Data, vector<Data>, decltype(cmp)> pq(cmp);
    for (int i = 0; i < n; i++) {
        dis[i] = -1;
        vis[i] = false;
    }
    for (int i = head[u]; i != -1; i = nxt[i]) {
        Data t = to[i];
        dis[t.v] = t.w;
        pq.push(t);
    }
    int res = -1;
    while (!pq.empty()) {
        Data t = pq.top();
        pq.pop();
        if (vis[t.v]) {
            continue;
        }
        vis[t.v] = true;
        for (int i = head[t.v]; i != -1; i = nxt[i]) {
            Data e = to[i];
            int a = t.w + e.w;
            if (dis[e.v] == -1 || dis[e.v] > a) {
                dis[e.v] = a;
                pq.push({e.v, a});
            }
        }
    }
}

int main() {
    int n = 10;
    vector<vector<int>> edges = {{0, 1, 3}, {1, 3, 2}, {3, 1, 1}, {0, 2, 2},
                                 {2, 0, 4}, {2, 3, 4}, {3, 2, 8}};
    int m = edges.size();
    init(n);
    for (int i = 0; i < m; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        int w = edges[i][2];
        addEdge(u, v, w);
    }
    dijkstra(0, n);
    printf("dis[9]: %d\n", dis[9]);  // dis[9]: -1
    printf("dis[3]: %d\n", dis[3]);  // dis[9]: 5
    return 0;
}