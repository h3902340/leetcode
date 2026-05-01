#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int M = 200;
const int N = 200;
const int K = 1000;
int dp[M][N][K + 1];
class Solution {
   public:
    int maxPathScore(vector<vector<int>>& grid, int k) {
        int m = grid.size();
        int n = grid[0].size();
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                for (int l = 0; l <= k; l++) {
                    dp[i][j][l] = -1;
                }
            }
        }
        dp[0][0][0] = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                bool cost = grid[i][j] > 0;
                if (i > 0) {
                    for (int l = 0; l <= k - cost; l++) {
                        if (dp[i - 1][j][l] == -1) {
                            continue;
                        }
                        dp[i][j][l + cost] = max(dp[i][j][l + cost],
                                                 grid[i][j] + dp[i - 1][j][l]);
                    }
                }
                if (j > 0) {
                    for (int l = 0; l <= k - cost; l++) {
                        if (dp[i][j - 1][l] == -1) {
                            continue;
                        }
                        dp[i][j][l + cost] = max(dp[i][j][l + cost],
                                                 grid[i][j] + dp[i][j - 1][l]);
                    }
                }
            }
        }
        int res = -1;
        for (int l = k; l >= 0; l--) {
            res = max(res, dp[m - 1][n - 1][l]);
        }
        return res;
    }
};

int main() {
    string problemName = "3742";
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
        getline(file_in, line_in);
        auto k = jread_int(line_in);
        auto res = sol.maxPathScore(grid, k);
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