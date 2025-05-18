#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

struct Pos {
    int x;
    int y;
};
const int PORTAL_TYPE_COUNT = 26;
const int MMAX = 1000;
const int NMAX = 1000;
vector<Pos> portals[PORTAL_TYPE_COUNT];
int dis[MMAX][NMAX];
Pos q[MMAX * NMAX];
int dir[4][2]{{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
class Solution {
   public:
    int minMoves(vector<string>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        if (m == 1 && n == 1) return 0;
        for (int i = 0; i < PORTAL_TYPE_COUNT; i++) {
            portals[i].clear();
        }
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                dis[i][j] = -1;
                if (matrix[i][j] == '.' || matrix[i][j] == '#') {
                    continue;
                }
                portals[matrix[i][j] - 'A'].push_back({i, j});
            }
        }
        int l = 1;
        int i = 0;
        int j = 1;
        q[0].x = 0;
        q[0].y = 0;
        Pos f = q[i];
        char c = matrix[f.x][f.y];
        if (c != '.' && c != '#') {
            for (auto p : portals[c - 'A']) {
                if (p.x == m - 1 && p.y == n - 1) return 0;
                dis[p.x][p.y] = 0;
                q[j].x = p.x;
                q[j].y = p.y;
                j++;
            }
        }
        while (i < j) {
            int r = j;
            for (; i < r; i++) {
                Pos f = q[i];
                for (int k = 0; k < 4; k++) {
                    int x = f.x + dir[k][0];
                    int y = f.y + dir[k][1];
                    if (x < 0 || y < 0 || x >= m || y >= n ||
                        matrix[x][y] == '#' || dis[x][y] != -1)
                        continue;
                    if (x == m - 1 && y == n - 1) return l;
                    dis[x][y] = l;
                    q[j].x = x;
                    q[j].y = y;
                    j++;
                }
            }
            r = j;
            for (int k = i; k < r; k++) {
                Pos f = q[k];
                char c = matrix[f.x][f.y];
                if (c != '.' && c != '#') {
                    for (auto p : portals[c - 'A']) {
                        if (dis[p.x][p.y] == -1) {
                            if (p.x == m - 1 && p.y == n - 1) return l;
                            dis[p.x][p.y] = l;
                            q[j].x = p.x;
                            q[j].y = p.y;
                            j++;
                        }
                    }
                }
            }
            l++;
        }
        return dis[m - 1][n - 1];
    }
};

int main() {
    string problemName = "3552";
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
        auto grid = jread_vector_string(line_in);
        auto res = sol.minMoves(grid);
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
        jprint_int(res, "res");
        jprint_int(ans, "ans");
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