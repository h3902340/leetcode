#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

struct Coor {
    int i;
    int j;
};
const int N = 2e4;
Coor q[N];
const int DIR = 4;
const Coor dir[DIR]{{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

class Solution {
   public:
    int latestDayToCross(int row, int col, vector<vector<int>>& cells) {
        int l = 0;
        int r = cells.size();
        int res = l;
        vector<vector<int>> grid(row, vector<int>(col));
        while (l <= r) {
            for (int i = 0; i < row; i++) {
                for (int j = 0; j < col; j++) {
                    grid[i][j] = 0;
                }
            }
            int mid = (l + r) >> 1;
            for (int i = 0; i < mid; i++) {
                grid[cells[i][0] - 1][cells[i][1] - 1] = 1;
            }
            int x = 0;
            int y = 0;
            for (int j = 0; j < col; j++) {
                if (grid[0][j] == 0) {
                    q[y++] = {0, j};
                    grid[0][j] = 1;
                }
            }
            bool canCross = false;
            while (x < y) {
                Coor f = q[x++];
                if (f.i == row - 1) {
                    canCross = true;
                    break;
                }
                grid[f.i][f.j] = 1;
                for (int i = 0; i < DIR; i++) {
                    int a = f.i + dir[i].i;
                    int b = f.j + dir[i].j;
                    if (a < 0 || a >= row || b < 0 || b >= col) continue;
                    if (grid[a][b] == 1) continue;
                    if (a == row - 1) {
                        canCross = true;
                        break;
                    }
                    q[y++] = {a, b};
                    grid[a][b] = 1;
                }
                if (canCross) {
                    break;
                }
            }
            if (canCross) {
                l = mid + 1;
                res = mid;
            } else {
                r = mid - 1;
            }
        }
        return res;
    }
};

int main() {
    string problemName = "1970";
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
        auto row = jread_int(line_in);
        getline(file_in, line_in);
        auto col = jread_int(line_in);
        getline(file_in, line_in);
        auto cells = jread_vector2d(line_in);
        auto res = sol.latestDayToCross(row, col, cells);
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