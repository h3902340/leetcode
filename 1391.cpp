#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int dir[7][2][2]{{{0, 0}, {0, 0}},  {{0, -1}, {0, 1}}, {{-1, 0}, {1, 0}},
                       {{0, -1}, {1, 0}}, {{0, 1}, {1, 0}},  {{0, -1}, {-1, 0}},
                       {{0, 1}, {-1, 0}}};
const int M = 300;
const int N = 300;
int vis[M][N];
class Solution {
   public:
    bool hasValidPath(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                vis[i][j] = false;
            }
        }
        return dfs(0, 0, grid, m, n);
    }
    bool dfs(int i, int j, vector<vector<int>>& grid, int m, int n) {
        if (i == m - 1 && j == n - 1) {
            return true;
        }
        vis[i][j] = true;
        for (int k = 0; k < 2; k++) {
            int x = i + dir[grid[i][j]][k][0];
            int y = j + dir[grid[i][j]][k][1];
            if (x < 0 || y < 0 || x >= m || y >= n) {
                continue;
            }
            if (vis[x][y]) {
                continue;
            }
            bool ok = false;
            for (int l = 0; l < 2; l++) {
                if (dir[grid[x][y]][l][0] == -dir[grid[i][j]][k][0] &&
                    dir[grid[x][y]][l][1] == -dir[grid[i][j]][k][1]) {
                    ok = true;
                    break;
                }
            }
            if (!ok) {
                continue;
            }
            bool a = dfs(x, y, grid, m, n);
            if (a) {
                return true;
            }
        }
        return false;
    }
};

int main() {
    string problemName = "1391";
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
        auto res = sol.hasValidPath(grid);
        getline(file_out, line_out);
        auto ans = jread_bool(line_out);
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