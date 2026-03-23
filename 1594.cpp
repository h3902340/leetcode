#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define ll long long
const int MOD = 1e9 + 7;
const int M = 15;
const int N = 15;
ll dp[2][M][2];
class Solution {
   public:
    int maxProductPath(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        dp[0][0][0] = grid[0][0];
        dp[1][0][0] = grid[0][0];
        for (int i = 1; i < m; i++) {
            dp[0][i][0] = dp[0][i - 1][0] * grid[i][0];
            dp[1][i][0] = dp[0][i][0];
        }
        int p = 0;
        int q = 1;
        for (int j = 1; j < n; j++) {
            dp[0][0][q] = dp[0][0][p] * grid[0][j];
            dp[1][0][q] = dp[0][0][q];
            for (int i = 1; i < m; i++) {
                dp[0][i][q] = grid[i][j];
                dp[1][i][q] = grid[i][j];
                if (grid[i][j] > 0) {
                    dp[0][i][q] *= min(dp[0][i - 1][q], dp[0][i][p]);
                    dp[1][i][q] *= max(dp[1][i - 1][q], dp[1][i][p]);
                } else {
                    dp[0][i][q] *= max(dp[1][i - 1][q], dp[1][i][p]);
                    dp[1][i][q] *= min(dp[0][i - 1][q], dp[0][i][p]);
                }
            }
            swap(p, q);
        }
        ll res = max(dp[0][m - 1][p], dp[1][m - 1][p]);
        if (res < 0) {
            return -1;
        }
        return res % MOD;
    }
};

int main() {
    string problemName = "1594";
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
        auto grid = jread_vector2d(line_in);
        auto res = sol.maxProductPath(grid);
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