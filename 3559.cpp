#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int MOD = 1e9 + 7;
const int NMAX = 1e5;
vector<int> adj[NMAX];
int q[NMAX];
int s[NMAX];
int dp[NMAX][2];

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

bool isInit = false;
static void init() {
    if (isInit) return;
    dp[1][0] = 1;
    dp[1][1] = 1;
    for (int i = 2; i < NMAX; i++) {
        dp[i][0] = (dp[i - 1][0] + dp[i - 1][1]) % MOD;
        dp[i][1] = (dp[i - 1][1] + dp[i - 1][0]) % MOD;
    }
    isInit = true;
}

class Solution {
   public:
    vector<int> assignEdgeWeights(vector<vector<int>>& edges,
                                  vector<vector<int>>& queries) {
        init();
        int m = edges.size();
        int n = m + 1;
        for (int i = 0; i < n; i++) {
            adj[i].clear();
            vis[i] = false;
        }
        for (int i = 0; i < m; i++) {
            adj[edges[i][0] - 1].push_back(edges[i][1] - 1);
            adj[edges[i][1] - 1].push_back(edges[i][0] - 1);
        }
        buildLCA();
        vector<int> res;
        for (auto& q : queries) {
            int u = q[0] - 1;
            int v = q[1] - 1;
            int a = lca(u, v);
            int d = depth[u] - depth[a] + depth[v] - depth[a];
            res.push_back(dp[d][1]);
        }
        return res;
    }

   private:
    void buildLCA() {
        depth[0] = 0;
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
            int e = adj[t.u][t.i];
            if (vis[e]) {
                t.i++;
                if (t.i == adj[t.u].size()) {
                    r--;
                    continue;
                }
                e = adj[t.u][t.i];
            }
            sta[++r] = {e, 0};
            depth[e] = depth[t.u] + 1;
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
    string problemName = "3559";
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
        auto res = sol.assignEdgeWeights(edges, queries);
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