#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

struct Data {
    int i;
    int j;
    int d;
};
const int N = 400;
Data q[N * N];
int dir[5]{0, 1, 0, -1, 0};
deque<Data> q2;

class Solution {
   public:
    int maximumSafenessFactor(vector<vector<int>>& grid) {
        int n = grid.size();
        int l = 0;
        int r = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j]) {
                    q[r++] = {i, j, 1};
                }
            }
        }
        while (l < r) {
            Data u = q[l++];
            for (int k = 0; k < 4; k++) {
                int x = u.i + dir[k];
                int y = u.j + dir[k + 1];
                if (x < 0 || y < 0 || x >= n || y >= n) {
                    continue;
                }
                if (grid[x][y]) {
                    continue;
                }
                grid[x][y] = u.d + 1;
                q[r++] = {x, y, u.d + 1};
            }
        }
        q2.clear();
        q2.push_back({0, 0, grid[0][0]});
        int res = grid[0][0];
        grid[0][0] = 0;
        while (!q2.empty()) {
            Data u = q2.front();
            q2.pop_front();
            res = min(res, u.d);
            if (u.i == n - 1 && u.j == n - 1) {
                break;
            }
            for (int k = 0; k < 4; k++) {
                int x = u.i + dir[k];
                int y = u.j + dir[k + 1];
                if (x < 0 || y < 0 || x >= n || y >= n) {
                    continue;
                }
                if (!grid[x][y]) {
                    continue;
                }
                if (grid[x][y] < res) {
                    q2.push_back({x, y, grid[x][y]});
                } else {
                    q2.push_front({x, y, grid[x][y]});
                }
                grid[x][y] = 0;
            }
        }
        return res - 1;
    }
};

int main() {
    string problemName = "2812";
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
        auto res = sol.maximumSafenessFactor(grid);
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