#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define lg2(x) (31 - __builtin_clz(x))
const int N = 5e4;
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
    int rmq[WALKMAX][LOGWALKMAX];
    int depth[N];
    int to[M << 1];
    int nxt[M << 1];
    int head[N];
    int eCnt;

   public:
    int ws;
    int tin[N];
    int tout[N];
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
        ws = 0;
        tin[0] = 0;
        while (r >= 0) {
            Data& t = st[r];
            walk[ws] = t.u;
            if (t.i != -1 && par[t.u] == to[t.i]) {
                t.i = nxt[t.i];
            }
            if (t.i == -1) {
                r--;
                tout[t.u] = ws;
                ws++;
                continue;
            }
            ws++;
            int v = to[t.i];
            par[v] = t.u;
            st[++r] = {v, head[v]};
            tin[v] = ws;
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
        a = tout[a];
        b = tout[b];
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
class FenwickTree {
    int arr[WALKMAX + 1];
    int sz;

   public:
    void init(int n) {
        sz = n + 1;
        for (int i = 1; i < sz; i++) {
            arr[i] = 0;
        }
    }
    void update(int i, int delta) {
        i++;
        while (i < sz) {
            arr[i] ^= delta;
            i += i & -i;
        }
    }
    int query(int i) {
        i++;
        int s = 0;
        while (i > 0) {
            s ^= arr[i];
            i -= i & -i;
        }
        return s;
    }
};
LCA g;
FenwickTree t;

class Solution {
   public:
    vector<bool> palindromePath(int n, vector<vector<int>>& edges, string s,
                                vector<string>& queries) {
        int m = edges.size();
        int q = queries.size();
        g.init(n);
        for (int i = 0; i < m; i++) {
            int u = edges[i][0];
            int v = edges[i][1];
            g.addEdge(u, v);
            g.addEdge(v, u);
        }
        g.build();
        t.init(g.ws);
        for (int i = 0; i < n; i++) {
            int d = 1 << (s[i] - 'a');
            t.update(g.tin[i], d);
            if (g.tout[i] + 1 < g.ws) {
                t.update(g.tout[i] + 1, d);
            }
        }
        vector<bool> res;
        for (int i = 0; i < q; i++) {
            if (queries[i][0] == 'u') {
                int j = 7;
                int u = 0;
                while (queries[i][j] != ' ') {
                    u = u * 10 + queries[i][j] - '0';
                    j++;
                }
                j++;
                char b = queries[i][j];
                int diff = (1 << (b - 'a')) ^ (1 << (s[u] - 'a'));
                s[u] = b;
                t.update(g.tin[u], diff);
                if (g.tout[u] + 1 < g.ws) {
                    t.update(g.tout[u] + 1, diff);
                }
                continue;
            }
            int j = 6;
            int u = 0;
            while (queries[i][j] != ' ') {
                u = u * 10 + queries[i][j] - '0';
                j++;
            }
            j++;
            int v = 0;
            while (j < queries[i].size()) {
                v = v * 10 + queries[i][j] - '0';
                j++;
            }
            int lca = g.lca(u, v);
            int qxor =
                t.query(g.tin[u]) ^ t.query(g.tin[v]) ^ (1 << (s[lca] - 'a'));
            res.push_back(qxor == 0 || __builtin_popcount(qxor) == 1);
        }
        return res;
    }
};

int main() {
    string problemName = "3841";
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
        auto s = jread_string(line_in);
        getline(file_in, line_in);
        auto queries = jread_vector_string(line_in);
        auto res = sol.palindromePath(n, edges, s, queries);
        getline(file_out, line_out);
        auto ans = jread_vector_bool(line_out);
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