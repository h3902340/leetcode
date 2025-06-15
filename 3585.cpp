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
const int N = 1e5;
const int LOGN = 17;
long long dp[N][LOGN];
int w[N];
vector<Edge> adj[N];
int st[N];

// lca
struct Data {
    int u;
    int i;
};
const int WALKMAX = N * 2 - 1;
const int LOGWALKMAX = 18;
Data sta[N];
int parent[N][LOGN];
int walk[WALKMAX];
int walkIndex[N];
int rmq[WALKMAX][LOGWALKMAX];
int depth[N];

class Solution {
   public:
    vector<int> findMedian(int n, vector<vector<int>>& edges,
                           vector<vector<int>>& queries) {
        int m = queries.size();
        int lgn = log2(n);
        for (int i = 0; i < n; i++) {
            adj[i].clear();
        }
        for (auto& e : edges) {
            int u = e[0];
            int v = e[1];
            int w = e[2];
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }
        int r = 0;
        st[r] = 0;
        parent[0][0] = -1;
        while (r >= 0) {
            int t = st[r--];
            for (auto& e : adj[t]) {
                if (e.v == parent[t][0]) continue;
                dp[e.v][0] = e.w;
                st[++r] = e.v;
                parent[e.v][0] = t;
            }
        }
        for (int j = 1; j <= lgn; j++) {
            for (int i = 0; i < n; i++) {
                int p1 = parent[i][j - 1];
                if (p1 == -1) {
                    parent[i][j] = -1;
                    continue;
                }
                int p2 = parent[p1][j - 1];
                if (p2 == -1) {
                    parent[i][j] = -1;
                    continue;
                }
                dp[i][j] = dp[i][j - 1] + dp[p1][j - 1];
                parent[i][j] = p2;
            }
        }
        buildLCA();
        vector<int> res(m);
        for (int i = 0; i < m; i++) {
            vector<int>& q = queries[i];
            int u = q[0];
            int v = q[1];
            int a = lca(u, v);
            long long d1 = 0;
            while (u != a) {
                int j = log2(depth[u] - depth[a]);
                d1 += dp[u][j];
                u = parent[u][j];
            }
            long long d2 = 0;
            while (v != a) {
                int j = log2(depth[v] - depth[a]);
                d2 += dp[v][j];
                v = parent[v][j];
            }
            if (d1 == d2) {
                res[i] = a;
                continue;
            }
            double med = (double)(d1 + d2) / 2;
            if (d1 > d2) {
                u = q[0];
                d1 = 0;
                int t = a;
                while (u != t) {
                    int j = log2(depth[u] - depth[t]);
                    if (d1 + dp[u][j] >= med) {
                        int l = 0;
                        int r = j;
                        j = -1;
                        while (l <= r) {
                            int mid = (l + r) >> 1;
                            if (d1 + dp[u][mid] < med) {
                                l = mid + 1;
                                j = mid;
                            } else {
                                r = mid - 1;
                            }
                        }
                        if (j == -1) {
                            t = parent[u][0];
                            break;
                        }
                    }
                    d1 += dp[u][j];
                    u = parent[u][j];
                }
                res[i] = t;
                continue;
            }
            if (d1 < d2) {
                v = q[1];
                d2 = 0;
                int t = a;
                while (v != t) {
                    int j = log2(depth[v] - depth[t]);
                    if (d2 + dp[v][j] > med) {
                        int l = 0;
                        int r = j;
                        j = -1;
                        while (l <= r) {
                            int mid = (l + r) >> 1;
                            if (d2 + dp[v][mid] > med) {
                                r = mid - 1;
                            } else {
                                l = mid + 1;
                                j = mid;
                            }
                        }
                        if (j == -1) {
                            t = v;
                            break;
                        }
                    }
                    d2 += dp[v][j];
                    v = parent[v][j];
                }
                res[i] = t;
            }
        }
        return res;
    }
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
            if (t.i == adj[t.u].size()) {
                r--;
                continue;
            }
            Edge& e = adj[t.u][t.i];
            if (parent[t.u][0] == e.v) {
                t.i++;
                if (t.i == adj[t.u].size()) {
                    r--;
                    continue;
                }
                e = adj[t.u][t.i];
            }
            sta[++r] = {e.v, 0};
            depth[e.v] = depth[t.u] + 1;
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
    int lca(int u, int v) {
        int uWalk = walkIndex[u];
        int vWalk = walkIndex[v];
        if (uWalk > vWalk) {
            swap(uWalk, vWalk);
        }
        int k = 1;
        int j = 0;
        while (uWalk + k - 1 <= vWalk) {
            k *= 2;
            j++;
        }
        j--;
        int uMin = rmq[uWalk][j];
        k = 1;
        j = 0;
        while (uWalk <= vWalk - k + 1) {
            k *= 2;
            j++;
        }
        j--;
        k /= 2;
        int vMin = rmq[vWalk - k + 1][j];
        int a = depth[uMin] < depth[vMin] ? uMin : vMin;
        return a;
    }
};

int main() {
    string problemName = "3585";
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
        auto queries = jread_vector2d(line_in);
        auto res = sol.findMedian(n, edges, queries);
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
        jprint(n, "n");
        // jprint(edges, "edges");
        // jprint(queries, "queries");
        //  jprint(res, "res");
        //  jprint(ans, "ans");
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