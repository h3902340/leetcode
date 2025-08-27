#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

struct Data {
    int len;
    int len1;
};
const int N = 500;
const int M = 500;
const int DIR_CNT = 4;
const int DIR[DIR_CNT][2]{{-1, -1}, {-1, 1}, {1, 1}, {1, -1}};
Data dp[DIR_CNT][N][M];

class Solution {
   public:
    int lenOfVDiagonal(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        int res = 0;
        for (int k = 0; k < DIR_CNT; k++) {
            int x = DIR[k][0];
            int y = DIR[k][1];
            if (k < 2) {
                for (int i = 0; i < n; i++) {
                    build(grid, n, m, k, i, x, y, res);
                }
            } else {
                for (int i = n - 1; i >= 0; i--) {
                    build(grid, n, m, k, i, x, y, res);
                }
            }
        }
        for (int k = 0; k < DIR_CNT; k++) {
            int l = k + 1;
            if (l == DIR_CNT) {
                l = 0;
            }
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    if (dp[l][i][j].len1 == 0) {
                        continue;
                    }
                    int a = dp[l][i][j].len1 + dp[k][i][j].len - 1;
                    res = max(res, a);
                }
            }
        }
        return res;
    }
    void build(vector<vector<int>>& grid, int n, int m, int k, int i, int x,
               int y, int& res) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 1) {
                dp[k][i][j].len = 0;
                dp[k][i][j].len1 = 1;
            } else {
                int a = i + x;
                int b = j + y;
                if (a < 0 || a >= n || b < 0 || b >= m ||
                    grid[i][j] == grid[a][b]) {
                    dp[k][i][j].len = 1;
                    dp[k][i][j].len1 = 0;
                } else {
                    dp[k][i][j].len = 1 + dp[k][a][b].len;
                    if (grid[a][b] == 1) {
                        if (grid[i][j] == 0) {
                            dp[k][i][j].len1 = 0;
                        } else {
                            dp[k][i][j].len1 = 2;
                        }
                    } else {
                        if (dp[k][a][b].len1 == 0) {
                            dp[k][i][j].len1 = 0;
                        } else {
                            dp[k][i][j].len1 = 1 + dp[k][a][b].len1;
                        }
                    }
                }
            }
            res = max(res, dp[k][i][j].len1);
        }
    }
};

int main() {
    string problemName = "3459";
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
        auto res = sol.lenOfVDiagonal(grid);
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