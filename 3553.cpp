#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

struct Edge {
    int v;
    int w;
};
const int NMAX = 1e5;
const int K = 3;
vector<Edge> adj[NMAX];
int w[NMAX];

// lca
struct Data {
    int u;
    int i;
};
const int WALKMAX = NMAX * 2 - 1;
const int LOGWALKMAX = 18;
Data sta[NMAX];
bool vis[NMAX];
int walk[WALKMAX];
int walkIndex[NMAX];
int rmq[WALKMAX][LOGWALKMAX];
int depth[NMAX];

class Solution {
   public:
    vector<int> minimumWeight(vector<vector<int>>& edges,
                              vector<vector<int>>& queries) {
        int n = edges.size() + 1;
        int m = queries.size();
        for (int i = 0; i < n; i++) {
            adj[i].clear();
            vis[i] = false;
        }
        for (auto e : edges) {
            adj[e[0]].push_back({e[1], e[2]});
            adj[e[1]].push_back({e[0], e[2]});
        }
        buildLCA();
        vector<int> ans(m);
        for (int i = 0; i < m; i++) {
            ans[i] = 0;
            for (int j = 0; j < K; j++) {
                ans[i] += w[queries[i][j]];
                for (int k = j + 1; k < K; k++) {
                    int p = lca(queries[i][j], queries[i][k]);
                    ans[i] -= w[p];
                }
            }
        }
        return ans;
    }

   private:
    void buildLCA() {
        depth[0] = 0;
        w[0] = 0;
        int r = 0;
        sta[0] = {0, 0};
        int ws = 0;
        while (r >= 0) {
            Data& t = sta[r];
            walk[ws] = t.u;
            walkIndex[t.u] = ws;
            ws++;
            vis[t.u] = true;
            if (t.i == adj[t.u].size()) {
                r--;
                continue;
            }
            Edge& e = adj[t.u][t.i];
            if (vis[e.v]) {
                t.i++;
                if (t.i == adj[t.u].size()) {
                    r--;
                    continue;
                }
                e = adj[t.u][t.i];
            }
            sta[++r] = {e.v, 0};
            depth[e.v] = depth[t.u] + 1;
            w[e.v] = w[t.u] + e.w;
            t.i++;
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
};

int main() {
    string problemName = "3553";
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
        auto edges = jread_vector2d(line_in);
        getline(file_in, line_in);
        auto queries = jread_vector2d(line_in);
        auto res = sol.minimumWeight(edges, queries);
        getline(file_out, line_out);
        auto ans = jread_vector(line_out);
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