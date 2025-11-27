#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int N = 5e4;
const int K = 50;
const int MOD = 1e9 + 7;
int dp[2][N][K];
int add(int a, int b) {
    a += b;
    if (a >= MOD) {
        a -= MOD;
    }
    return a;
}

class Solution {
   public:
    int numberOfPaths(vector<vector<int>>& grid, int k) {
        int m = grid.size();
        int n = grid[0].size();
        int a = 0;
        if (n == 1) {
            for (int i = 0; i < m; i++) {
                a = (a + grid[i][0]) % k;
            }
            if (a == 0) {
                return 1;
            }
            return 0;
        }
        for (int j = 0; j < n; j++) {
            for (int l = 0; l < k; l++) {
                dp[0][j][l] = 0;
            }
            a = (a + grid[0][j]) % k;
            dp[0][j][a] = 1;
        }
        bool p = false;
        a = grid[0][0];
        for (int i = 1; i < m; i++) {
            p = !p;
            a = (a + grid[i][0]) % k;
            int r = grid[i][1] % k;
            for (int l = 0; l < k; l++) {
                dp[p][1][r] = dp[!p][1][l];
                r++;
                if (r >= k) {
                    r -= k;
                }
            }
            dp[p][1][(a + grid[i][1]) % k]++;
            for (int j = 2; j < n; j++) {
                int r = grid[i][j] % k;
                for (int l = 0; l < k; l++) {
                    dp[p][j][r] = add(dp[p][j - 1][l], dp[!p][j][l]);
                    r++;
                    if (r >= k) {
                        r -= k;
                    }
                }
            }
        }
        return dp[p][n - 1][0];
    }
};

int main() {
    string problemName = "2435";
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
        auto res = sol.numberOfPaths(grid, k);
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