#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int N = 2e4;
const int DIR_LEN = 8;
const int DIR[DIR_LEN][2] = {{0, 1},   {1, 0},  {0, -1}, {-1, 0},
                             {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
int parent[N + 2];
int find(int u) {
    int p = u;
    while (parent[p] >= 0) {
        p = parent[p];
    }
    while (parent[u] >= 0) {
        int tmp = parent[u];
        parent[u] = p;
        u = tmp;
    }
    return p;
}
void unite(int u, int v) {
    int a = find(u);
    int b = find(v);
    if (b != a) {
        parent[b] = a;
    }
}
void init(int n) {
    for (int i = 0; i < n; i++) {
        parent[i] = -1;
    }
}

class Solution {
   public:
    int latestDayToCross(int row, int col, vector<vector<int>>& cells) {
        int n = cells.size();
        init(n + 2);
        int s = 0;
        int t = n + 1;
        int i = 0;
        for (; i < n; i++) {
            int x = cells[i][0];
            int y = cells[i][1];
            int v = (x - 1) * col + y;
            parent[v] = -2;
            for (int j = 0; j < DIR_LEN; j++) {
                int x2 = x + DIR[j][0];
                int y2 = y + DIR[j][1];
                if (x2 == 0 || x2 > row || y2 == 0 || y2 > col) {
                    continue;
                }
                int v2 = (x2 - 1) * col + y2;
                if (parent[v2] != -1) {
                    unite(v, v2);
                }
            }
            if (y == 1) {
                unite(s, v);
            } else if (y == col) {
                unite(t, v);
            }
            if (i < col - 1) {
                continue;
            }
            if (find(s) == find(t)) {
                break;
            }
        }
        return i;
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