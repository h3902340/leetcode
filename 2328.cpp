#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int dir[5]{0, 1, 0, -1, 0};
const int M = 1000;
const int N = 1000;
const int MOD = 1e9 + 7;
int memo[M][N];
int add(int a, int b) { return (a + b) % MOD; }
class Solution {
   public:
    int countPaths(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                memo[i][j] = 0;
            }
        }
        int res = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                res = add(res, dfs(i, j, grid, m, n));
            }
        }
        return res;
    }
    int dfs(int i, int j, vector<vector<int>>& grid, int m, int n) {
        if (memo[i][j] != 0) {
            return memo[i][j];
        }
        int res = 1;
        for (int k = 0; k < 4; k++) {
            int x = i + dir[k];
            int y = j + dir[k + 1];
            if (x < 0 || y < 0 || x >= m || y >= n) {
                continue;
            }
            if (grid[x][y] <= grid[i][j]) {
                continue;
            }
            res = add(res, dfs(x, y, grid, m, n));
        }
        memo[i][j] = res;
        return res;
    }
};

int main() {
    string problemName = "2328";
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
        auto res = sol.countPaths(grid);
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