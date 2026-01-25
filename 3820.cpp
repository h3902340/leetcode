#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define ll long long
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
const int M = N - 1;
int to[M << 1];
int nxt[M << 1];
int head[N];
int eCnt;
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
void addEdge(int u, int v) {
    to[eCnt] = v;
    nxt[eCnt] = head[u];
    head[u] = eCnt++;
}
void init(int n) {
    eCnt = 0;
    for (int i = 0; i < n; i++) {
        head[i] = -1;
        vis[i] = false;
    }
}
int nod[3];
int dis[3];

class Solution {
   public:
    int specialNodes(int n, vector<vector<int>>& edges, int x, int y, int z) {
        int m = edges.size();
        init(n);
        for (int i = 0; i < m; i++) {
            int u = edges[i][0];
            int v = edges[i][1];
            addEdge(u, v);
            addEdge(v, u);
        }
        buildLCA();
        nod[0] = x;
        nod[1] = y;
        nod[2] = z;
        int res = 0;
        for (int i = 0; i < n; i++) {
            int mxIdx = 0;
            for (int j = 0; j < 3; j++) {
                int a = lca(i, nod[j]);
                dis[j] = depth[i] - depth[a] + depth[nod[j]] - depth[a];
                if (j > 0) {
                    if (dis[mxIdx] < dis[j]) {
                        mxIdx = j;
                    }
                }
            }
            ll c = (ll)dis[mxIdx] * dis[mxIdx];
            for (int j = 0; j < 3; j++) {
                if (j == mxIdx) {
                    continue;
                }
                c -= (ll)dis[j] * dis[j];
            }
            if (c == 0) {
                res++;
            }
        }
        return res;
    }
};

int main() {
    string problemName = "3820";
    auto begin = jtimer();
    Solution sol;
    ifstream file_in("testcases/" + problemName + "_in.txt");
    ifstream file_out("testcases/" + problemName + "_out.txt");
    bool allPass = true;
    int caseCount = 0;
    int passCount = 0;
    string line_in;
    string line_out;
    while (getline(file_in, line_in)) {
        auto n = jread_int(line_in);
        getline(file_in, line_in);
        auto edges = jread_vector2d(line_in);
        getline(file_in, line_in);
        auto x = jread_int(line_in);
        getline(file_in, line_in);
        auto y = jread_int(line_in);
        getline(file_in, line_in);
        auto z = jread_int(line_in);
        auto res = sol.specialNodes(n, edges, x, y, z);
        getline(file_out, line_out);
        auto ans = jread_int(line_out);
        printf("Case %d", ++caseCount);
        if (res == ans) {
            passCount++;
            printf(" %s(PASS)", KGRN);
        } else {
            printf(" %s(WRONG)", KRED);
            allPass = false;
        }
        printf("\n%s", KNRM);
        jprint(res, "res");
        jprint(ans, "ans");
        printf("\n");
    }
    if (allPass) {
        printf("%sALL CORRECT [%d/%d]\n%s", KGRN, passCount, caseCount, KNRM);
    } else {
        printf("%sWRONG ANSWER [%d/%d]\n%s", KRED, passCount, caseCount, KNRM);
    }
    auto end = jtimer();
    jprint_time(begin, end);
    return 0;
}