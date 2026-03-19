#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

struct Data {
    int x;
    int y;
};
class Solution {
   public:
    int numberOfSubmatrices(vector<vector<char>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<Data>> dp(m, vector<Data>(n));
        int res = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 'X') {
                    dp[i][j].x++;
                } else if (grid[i][j] == 'Y') {
                    dp[i][j].y++;
                }
                if (i > 0) {
                    dp[i][j].x += dp[i - 1][j].x;
                    dp[i][j].y += dp[i - 1][j].y;
                }
                if (j > 0) {
                    dp[i][j].x += dp[i][j - 1].x;
                    dp[i][j].y += dp[i][j - 1].y;
                }
                if (i > 0 && j > 0) {
                    dp[i][j].x -= dp[i - 1][j - 1].x;
                    dp[i][j].y -= dp[i - 1][j - 1].y;
                }
                if (dp[i][j].x == dp[i][j].y && dp[i][j].x > 0) {
                    res++;
                }
            }
        }
        return res;
    }
};

int main() {
    string problemName = "3212";
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
        auto grid = jread_vector2d_char(line_in);
        auto res = sol.numberOfSubmatrices(grid);
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