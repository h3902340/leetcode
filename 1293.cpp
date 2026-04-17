#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

struct Data {
    int i;
    int j;
    int k;
    int l;
};
const int M = 40;
const int N = 40;
const int K = M * N;
const int DIR[5]{0, 1, 0, -1, 0};
Data q[M * N * (K + 1)];
bool vis[M][N][K + 1];
class Solution {
   public:
    int shortestPath(vector<vector<int>>& grid, int k) {
        int m = grid.size();
        int n = grid[0].size();
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = m * n - 1; k >= 0; k--) {
                    vis[i][j][k] = false;
                }
            }
        }
        int l = 0;
        int r = 1;
        q[0] = {0, 0, 0, 0};
        while (l < r) {
            Data u = q[l++];
            if (u.i == m - 1 && u.j == n - 1) {
                return u.l;
            }
            for (int i = 0; i < 4; i++) {
                int x = u.i + DIR[i];
                int y = u.j + DIR[i + 1];
                if (x < 0 || y < 0 || x >= m || y >= n) {
                    continue;
                }
                int z = u.k;
                if (grid[x][y] == 1) {
                    z++;
                }
                if (z > k) {
                    continue;
                }
                if (vis[x][y][z]) {
                    continue;
                }
                vis[x][y][z] = true;
                q[r++] = {x, y, z, u.l + 1};
            }
        }
        return -1;
    }
};

int main() {
    string problemName = "1293";
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
        auto res = sol.shortestPath(grid, k);
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