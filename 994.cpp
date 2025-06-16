#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

struct Coor {
    int i;
    int j;
    int t;
};
const int M = 10;
const int N = 10;
Coor q[M * N];
const int DIR = 4;
const int dir[DIR][2] = {{0, -1}, {0, 1}, {1, 0}, {-1, 0}};
class Solution {
   public:
    int orangesRotting(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        int cnt = 0;
        int l = 0;
        int r = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 2) {
                    q[r] = {i, j, 0};
                    r++;
                } else if (grid[i][j] == 1) {
                    cnt++;
                }
            }
        }
        int res = 0;
        while (l < r) {
            Coor f = q[l++];
            for (int i = 0; i < DIR; i++) {
                int x = f.i + dir[i][0];
                int y = f.j + dir[i][1];
                if (x < 0 || x >= m || y < 0 || y >= n) continue;
                if (grid[x][y] == 1) {
                    q[r++] = {x, y, f.t + 1};
                    grid[x][y] = 2;
                    res = f.t + 1;
                    cnt--;
                }
            }
        }
        if (cnt > 0) {
            return -1;
        }
        return res;
    }
};

int main() {
    string problemName = "994";
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
        auto res = sol.orangesRotting(grid);
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