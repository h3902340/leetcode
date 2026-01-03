#include <cmath>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int MOD = 1e9 + 7;
const int M = 750;
int dp[2][M];
int add(int a, int b) {
    a += b;
    if (a >= MOD) {
        a -= MOD;
    }
    return a;
}
int sub(int a, int b) {
    a -= b;
    if (a < 0) {
        a += MOD;
    }
    return a;
}
class Solution {
   public:
    int numberOfRoutes(vector<string>& grid, int d) {
        int n = grid.size();
        int m = grid[0].size();
        int a = d - 1;
        for (int j = 0; j < m; j++) {
            if (grid[0][j] == '#') {
                dp[0][j] = 0;
            } else {
                dp[0][j] = 1;
            }
            if (j > 0) {
                dp[0][j] += dp[0][j - 1];
            }
        }
        bool p = 1;
        bool q = 0;
        for (int j = 0; j < m; j++) {
            if (grid[0][j] == '#') {
                dp[p][j] = 0;
            } else {
                int l = max(j - d, 0);
                int r = min(j + d, m - 1);
                dp[p][j] = dp[q][r];
                if (l > 0) {
                    dp[p][j] -= dp[q][l - 1];
                }
            }
            if (j > 0) {
                dp[p][j] += dp[p][j - 1];
            }
        }
        swap(p, q);
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == '#') {
                    dp[p][j] = 0;
                } else {
                    int l = max(j - a, 0);
                    int r = min(j + a, m - 1);
                    dp[p][j] = dp[q][r];
                    if (l > 0) {
                        dp[p][j] = sub(dp[p][j], dp[q][l - 1]);
                    }
                }
                if (j > 0) {
                    dp[p][j] = add(dp[p][j], dp[p][j - 1]);
                }
            }
            swap(p, q);
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == '#') {
                    dp[p][j] = 0;
                } else {
                    int l = max(j - d, 0);
                    int r = min(j + d, m - 1);
                    dp[p][j] = dp[q][r];
                    if (l > 0) {
                        dp[p][j] = sub(dp[p][j], dp[q][l - 1]);
                    }
                }
                if (j > 0) {
                    dp[p][j] = add(dp[p][j], dp[p][j - 1]);
                }
            }
            swap(p, q);
        }
        return dp[q][m - 1];
    }
};

int main() {
    string problemName = "3797";
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
        auto grid = jread_vector_string(line_in);
        getline(file_in, line_in);
        auto d = jread_int(line_in);
        auto res = sol.numberOfRoutes(grid, d);
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