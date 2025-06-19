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
const int M = 200;
const int N = 200;
int state[M][N];
Coor q[M * N];
const int DIR = 4;
const Coor dir[DIR]{{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
class Solution {
   public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        int m = heights.size();
        int n = heights[0].size();
        if (m == 1 && n == 1) return {{0, 0}};
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                state[i][j] = 0;
            }
        }
        vector<vector<int>> res;
        int l = 0;
        int r = 0;
        for (int i = 0; i < m; i++) {
            state[i][0] = 1;
            q[r++] = {i, 0};
        }
        for (int j = 1; j < n; j++) {
            state[0][j] = 1;
            q[r++] = {0, j};
        }
        while (l < r) {
            Coor f = q[l++];
            for (int i = 0; i < DIR; i++) {
                int x = f.i + dir[i].i;
                int y = f.j + dir[i].j;
                if (x < 0 || x >= m || y < 0 || y >= n) continue;
                if (heights[f.i][f.j] > heights[x][y]) continue;
                if (state[x][y] & 1) continue;
                q[r++] = {x, y};
                state[x][y] |= 1;
            }
        }
        l = 0;
        r = 0;
        for (int i = 0; i < m; i++) {
            state[i][n - 1] |= 2;
            q[r++] = {i, n - 1};
        }
        for (int j = 0; j < n - 1; j++) {
            state[m - 1][j] |= 2;
            q[r++] = {m - 1, j};
        }
        while (l < r) {
            Coor f = q[l++];
            if (state[f.i][f.j] == 3) {
                res.push_back({f.i, f.j});
            }
            for (int i = 0; i < DIR; i++) {
                int x = f.i + dir[i].i;
                int y = f.j + dir[i].j;
                if (x < 0 || x >= m || y < 0 || y >= n) continue;
                if (heights[f.i][f.j] > heights[x][y]) continue;
                if (state[x][y] & 2) continue;
                q[r++] = {x, y};
                state[x][y] |= 2;
            }
        }
        return res;
    }
};

int main() {
    string problemName = "417";
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
        auto heights = jread_vector2d(line_in);
        auto res = sol.pacificAtlantic(heights);
        getline(file_out, line_out);
        auto ans = jread_vector2d(line_out);
        printf("Case %d", ++caseCount);
        if (coorEqual(res, ans)) {
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