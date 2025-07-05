#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

// TODO: use dp instead
#define ll long long

class Solution {
   public:
    vector<vector<ll>> memo;
    long long minCost(int m, int n, vector<vector<int>>& waitCost) {
        memo = vector<vector<ll>>(m, vector<ll>(n, -1));
        ll res = dfs(0, 0, m, n, waitCost);
        res = res - waitCost[0][0] - waitCost[m - 1][n - 1];
        return res;
    }
    ll dfs(int i, int j, int m, int n, vector<vector<int>>& waitCost) {
        if (memo[i][j] != -1) {
            return memo[i][j];
        }
        ll cost = (i + 1) * (j + 1) + waitCost[i][j];
        if (i == m - 1 && j == n - 1) {
            memo[i][j] = cost;
            return cost;
        }
        ll res = __LONG_LONG_MAX__;
        if (j + 1 < n) {
            ll right = cost + dfs(i, j + 1, m, n, waitCost);
            res = min(res, right);
        }
        if (i + 1 < m) {
            ll down = cost + dfs(i + 1, j, m, n, waitCost);
            res = min(res, down);
        }
        memo[i][j] = res;
        return res;
    }
};

int main() {
    string problemName = "3603";
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
        auto m = jread_int(line_in);
        getline(file_in, line_in);
        auto n = jread_int(line_in);
        getline(file_in, line_in);
        auto waitCost = jread_vector2d(line_in);
        auto res = sol.minCost(m, n, waitCost);
        getline(file_out, line_out);
        auto ans = jread_longlong(line_out);
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