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
int parent[NMAX];
int dp[NMAX][2];
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
    int assignEdgeWeights(vector<vector<int>>& edges) {
        init();
        int m = edges.size();
        int n = m + 1;
        for (int i = 0; i < n; i++) {
            adj[i].clear();
        }
        for (int i = 0; i < m; i++) {
            adj[edges[i][0] - 1].push_back(edges[i][1] - 1);
            adj[edges[i][1] - 1].push_back(edges[i][0] - 1);
        }
        int l = 0;
        int r = 1;
        q[0] = 0;
        parent[0] = -1;
        while (l < r) {
            int f = q[l++];
            int p = parent[f];
            for (auto& e : adj[f]) {
                if (e == p) continue;
                q[r++] = e;
                parent[e] = f;
            }
        }
        int d = 0;
        int leaf = q[r - 1];
        while (leaf != 0) {
            leaf = parent[leaf];
            d++;
        }
        return dp[d][1];
    }
};

int main() {
    string problemName = "3558";
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
        auto res = sol.assignEdgeWeights(edges);
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