#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define ll long long
const int N = 100;
ll dp[N][N + 1][N + 1];
ll pre[N][N + 1];
ll pre2[N][N + 1][N + 1];
ll pre3[N][N + 1][N + 1];
ll col[N][N + 1];
class Solution {
   public:
    long long maximumScore(vector<vector<int>>& grid) {
        int n = grid.size();
        if (n == 1) {
            return 0;
        }
        for (int j = 0; j < n; j++) {
            for (int i = 0; i < n; i++) {
                col[j][i + 1] = col[j][i] + grid[i][j];
            }
        }
        for (int j = 0; j <= n; j++) {
            for (int k = 0; k <= n; k++) {
                if (j < k) {
                    dp[0][j][k] = col[0][k] - col[0][j];
                } else {
                    dp[0][j][k] = col[1][j] - col[1][k];
                }
            }
        }
        for (int i = 1; i < n - 1; i++) {
            for (int k = 0; k <= n; k++) {
                pre[i - 1][k] = 0;
                for (int j = 0; j < k; j++) {
                    pre[i - 1][k] = max(pre[i - 1][k], dp[i - 1][j][k]);
                }
                pre2[i - 1][k][k] = dp[i - 1][k][k] - col[i][k] + col[i][k];
                for (int j = k + 1; j <= n; j++) {
                    pre2[i - 1][j][k] =
                        max(pre2[i - 1][j - 1][k],
                            dp[i - 1][j][k] - col[i][j] + col[i][k]);
                }
                pre3[i - 1][n][k] = dp[i - 1][n][k];
                for (int j = n - 1; j >= k; j--) {
                    pre3[i - 1][j][k] =
                        max(pre3[i - 1][j + 1][k], dp[i - 1][j][k]);
                }
            }
            for (int j = 0; j <= n; j++) {
                for (int k = 0; k <= n; k++) {
                    if (j < k) {
                        dp[i][j][k] =
                            max({pre[i - 1][j] + col[i][k] - col[i][j],
                                 pre2[i - 1][k][j] + col[i][k] - col[i][j],
                                 pre3[i - 1][k][j]});
                    } else {
                        dp[i][j][k] = max(pre[i - 1][j], pre3[i - 1][j][j]) +
                                      col[i + 1][j] - col[i + 1][k];
                    }
                }
            }
        }
        ll res = 0;
        for (int j = 0; j <= n; j++) {
            for (int k = 0; k <= n; k++) {
                res = max(res, dp[n - 2][j][k]);
            }
        }
        return res;
    }
};

int main() {
    string problemName = "3225";
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
        auto res = sol.maximumScore(grid);
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