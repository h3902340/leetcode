#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int N = 1e5;
const int M = N - 1;
const int C = 3;
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
int par[N];
int lev[N];
bool dp[N][C];
bool can[N];

class Solution {
   public:
    vector<int> smallestThreeColorTree(int n, vector<vector<int>>& edges) {
        int m = edges.size();
        init(n);
        for (int i = 0; i < m; i++) {
            int u = edges[i][0];
            int v = edges[i][1];
            addEdge(u, v);
            addEdge(v, u);
        }
        lev[0] = 0;
        par[0] = -1;
        int l = 0;
        int r = 1;
        while (l < r) {
            int u = lev[l++];
            for (int i = head[u]; i != -1; i = nxt[i]) {
                int v = to[i];
                if (par[u] == v) {
                    continue;
                }
                par[v] = u;
                lev[r++] = v;
            }
        }
        vector<int> res(n, -1);
        for (int i = 0; i < n; i++) {
            for (int k = 0; k < C; k++) {
                can[k] = true;
            }
            for (int j = head[i]; j != -1; j = nxt[j]) {
                int v = to[j];
                if (res[v] != -1) {
                    can[res[v]] = false;
                }
            }
            for (int k = 0; k < C; k++) {
                dp[i][k] = false;
            }
            for (int k = 0; k < C; k++) {
                if (!can[k]) {
                    continue;
                }
                dp[i][k] = true;
                if (k > 0) {
                    dp[i - 1][k] = false;
                }
                res[i] = k;
                if (check(n, res)) {
                    break;
                }
            }
        }
        return res;
    }
    bool check(int n, vector<int>& res) {
        for (int i = n - 1; i >= 0; i--) {
            int u = lev[i];
            if (res[u] != -1) {
                for (int j = head[u]; j != -1; j = nxt[j]) {
                    int v = to[j];
                    if (par[u] == v) {
                        continue;
                    }
                    int c = res[v];
                    if (c == -1) {
                        int cnt = 0;
                        for (int k = 0; k < C; k++) {
                            if (dp[v][k]) {
                                cnt++;
                                c = k;
                            }
                        }
                        if (cnt > 1) {
                            c = -1;
                        }
                    }
                    if (res[u] == c) {
                        return false;
                    }
                }
                continue;
            }
            for (int k = 0; k < C; k++) {
                dp[u][k] = true;
            }
            for (int j = head[u]; j != -1; j = nxt[j]) {
                int v = to[j];
                if (par[u] == v) {
                    continue;
                }
                int cnt = 0;
                int c = -1;
                for (int k = 0; k < C; k++) {
                    if (dp[v][k]) {
                        cnt += dp[v][k];
                        c = k;
                    }
                }
                if (cnt == 1) {
                    dp[u][c] = false;
                }
            }
            bool ok = false;
            for (int k = 0; k < C; k++) {
                if (dp[u][k]) {
                    ok = true;
                    break;
                }
            }
            if (!ok) {
                return false;
            }
        }
        return true;
    }
};

int main() {
    string problemName = "SmallestThreeColorTree";
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
        auto res = sol.smallestThreeColorTree(n, edges);
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