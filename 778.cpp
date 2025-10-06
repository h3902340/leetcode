#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

struct Pos {
    int i;
    int j;
};
const int NIL = -1;
const int N = 50;
const int DIR[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
int parent[N * N];
Pos mp[N * N];
class Solution {
   public:
    int swimInWater(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                mp[grid[i][j]] = {i, j};
                parent[grid[i][j]] = NIL;
            }
        }
        int start = grid[0][0];
        int end = grid[m - 1][n - 1];
        int len = m * n;
        for (int i = 0; i < len; i++) {
            Pos& pos = mp[i];
            for (auto& d : DIR) {
                int x = pos.i + d[0];
                int y = pos.j + d[1];
                if (x < 0 || x >= m || y < 0 || y >= n) {
                    continue;
                }
                if (grid[x][y] < i) {
                    int p1 = find(grid[x][y]);
                    int p2 = find(i);
                    if (p1 != p2) {
                        parent[p1] = p2;
                    }
                }
            }
            if (find(start) == find(end)) {
                return i;
            }
        }
        return -1;
    }
    int find(int u) {
        int p = u;
        while (parent[p] != NIL) {
            p = parent[p];
        }
        // collapsing
        while (parent[u] != NIL) {
            int tmp = parent[u];
            parent[u] = p;
            u = tmp;
        }
        return p;
    }
};

int main() {
    string problemName = "778";
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
        auto res = sol.swimInWater(grid);
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