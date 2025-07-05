#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int N = 1e5;
const int D = 14;
vector<int> adj[N];
int memo[N][D + 1];

class Solution {
   public:
    int maximumPoints(vector<vector<int>>& edges, vector<int>& coins, int k) {
        int n = coins.size();
        for (int i = 0; i < n; i++) {
            adj[i].clear();
            for (int j = 0; j <= D; j++) {
                memo[i][j] = -1;
            }
        }
        for (auto& e : edges) {
            int u = e[0];
            int v = e[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        return dfs(0, 0, -1, coins, k);
    }
    int dfs(int i, int d, int p, vector<int>& coins, int k) {
        if (d == D) {
            return 0;
        }
        if (memo[i][d] != -1) {
            return memo[i][d];
        }
        int w = coins[i] >> d;
        int a = w - k;
        int b = w >> 1;
        for (auto e : adj[i]) {
            if (e == p) continue;
            a += dfs(e, d, i, coins, k);
            b += dfs(e, d + 1, i, coins, k);
        }
        int res = max(a, b);
        memo[i][d] = res;
        return res;
    }
};

int main() {
    string problemName = "2920";
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
        auto coins = jread_vector(line_in);
        getline(file_in, line_in);
        auto k = jread_int(line_in);
        auto res = sol.maximumPoints(edges, coins, k);
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