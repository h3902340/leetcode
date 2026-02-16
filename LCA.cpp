#include "Jutil.h"
using namespace std;

#define lg2(x) (31 - __builtin_clz(x))
const int N = 1e5;
const int WALKMAX = (N << 1) - 1;
const int LOGWALKMAX = lg2(WALKMAX) + 1;
const int M = N - 1;
class LCA {
    struct Data {
        int u;
        int i;
    };
    Data st[N];
    int par[N];
    int walk[WALKMAX];
    int walkIndex[N];
    int rmq[WALKMAX][LOGWALKMAX];
    int depth[N];
    int to[M << 1];
    int nxt[M << 1];
    int head[N];
    int eCnt;

   public:
    void init(int n) {
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
    void build() {
        depth[0] = 0;
        int r = 0;
        st[0] = {0, head[0]};
        par[0] = -1;
        int ws = 0;
        while (r >= 0) {
            Data& t = st[r];
            walk[ws] = t.u;
            walkIndex[t.u] = ws;
            ws++;
            if (t.i == -1) {
                r--;
                continue;
            }
            int v = to[t.i];
            if (par[t.u] == v) {
                t.i = nxt[t.i];
                if (t.i == -1) {
                    r--;
                    continue;
                }
                v = to[t.i];
            }
            par[v] = t.u;
            st[++r] = {v, head[v]};
            depth[v] = depth[t.u] + 1;
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
        int j = lg2(b - a + 1);
        int k = 1 << j;
        int mina = rmq[a][j];
        int minb = rmq[b - k + 1][j];
        return depth[mina] < depth[minb] ? mina : minb;
    }
};
LCA g;

int main() {
    int n = 100;
    vector<vector<int>> edges = {{0, 1}, {1, 2}, {1, 3}, {4, 2},
                                 {3, 5}, {4, 6}, {4, 7}, {1, 8}};
    int m = edges.size();
    g.init(n);
    for (int i = 0; i < m; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        g.addEdge(u, v);
        g.addEdge(v, u);
    }
    g.build();
    int res = g.lca(2, 3);
    printf("res: %d\n", res);  // res: 1
    return 0;
}