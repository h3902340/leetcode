#include "Jutil.h"
using namespace std;

// LCA
struct Data {
    int u;
    int i;
};
const int N = 1e5;
const int WALKMAX = (N << 1) - 1;
const int LOGWALKMAX = 18;
Data st[N];
bool vis[N];
int walk[WALKMAX];
int walkIndex[N];
int rmq[WALKMAX][LOGWALKMAX];
int depth[N];
void buildLCA() {
    depth[0] = 0;
    int r = 0;
    st[0] = {0, head[0]};
    int ws = 0;
    while (r >= 0) {
        Data& t = st[r];
        walk[ws] = t.u;
        walkIndex[t.u] = ws;
        ws++;
        vis[t.u] = true;
        if (t.i == -1) {
            r--;
            continue;
        }
        int e = to[t.i];
        if (vis[e]) {
            t.i = nxt[t.i];
            if (t.i == -1) {
                r--;
                continue;
            }
            e = to[t.i];
        }
        st[++r] = {e, head[e]};
        depth[e] = depth[t.u] + 1;
        t.i = nxt[t.i];
    }
    for (int i = 0; i < ws; i++) {
        rmq[i][0] = walk[i];
    }
    int k = 1;
    for (int j = 1; k < ws; j++) {
        for (int i = 0; i + k * 2 - 1 < ws; i++) {
            int a = rmq[i][j - 1];
            int b = rmq[i + k][j - 1];
            rmq[i][j] = depth[a] < depth[b] ? a : b;
        }
        k *= 2;
    }
}
int lca(int a, int b) {
    a = walkIndex[a];
    b = walkIndex[b];
    if (a > b) {
        swap(a, b);
    }
    int k = 1;
    int j = 0;
    while (a + k - 1 <= b) {
        k *= 2;
        j++;
    }
    j--;
    int mina = rmq[a][j];
    k = 1;
    j = 0;
    while (a <= b - k + 1) {
        k *= 2;
        j++;
    }
    j--;
    k /= 2;
    int minb = rmq[b - k + 1][j];
    return depth[mina] < depth[minb] ? mina : minb;
}

// CSR Graph
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
    int n = 4;
    vector<vector<int>> edges = {{0, 1}, {1, 2}, {1, 3}};
    int m = edges.size();
    init(n);
    for (int i = 0; i < m; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        addEdge(u, v);
        addEdge(v, u);
    }
    buildLCA();
    int res = lca(2, 3);
    printf("res: %d\n", res);  // res: 1
    return 0;
}