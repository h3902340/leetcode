#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int M = 500;
const int N = 500;
const int dir[5]{0, 1, 0, -1, 0};
bool vis[M][N];
class Solution {
   public:
    bool containsCycle(vector<vector<char>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                vis[i][j] = false;
            }
        }
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (vis[i][j]) {
                    continue;
                }
                bool a = dfs(i, j, -1, -1, grid, m, n);
                if (a) {
                    return true;
                }
            }
        }
        return false;
    }
    bool dfs(int i, int j, int prei, int prej, vector<vector<char>>& grid,
             int m, int n) {
        vis[i][j] = true;
        for (int k = 0; k < 4; k++) {
            int x = i + dir[k];
            int y = j + dir[k + 1];
            if (x < 0 || y < 0 || x >= m || y >= n) {
                continue;
            }
            if (grid[x][y] != grid[i][j]) {
                continue;
            }
            if (vis[x][y]) {
                if (x != prei || y != prej) {
                    return true;
                }
                continue;
            }
            bool a = dfs(x, y, i, j, grid, m, n);
            if (a) {
                return true;
            }
        }
        return false;
    }
};

int main() {
    string problemName = "1559";
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
        auto res = sol.containsCycle(grid);
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