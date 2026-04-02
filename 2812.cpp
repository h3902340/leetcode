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
const int NN = N * N;
Data q[NN];
class DSU {
    int parent[NN];
    int sz[NN];

   public:
    void init(int n) {
        for (int i = 0; i < n; i++) {
            parent[i] = -1;
            sz[i] = 1;
        }
    }
    int find(int u) {
        int p = u;
        while (parent[p] != -1) {
            p = parent[p];
        }
        while (parent[u] != -1) {
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
            if (sz[b] < sz[a]) {
                parent[b] = a;
                sz[a] += sz[b];
            } else {
                parent[a] = b;
                sz[b] += sz[a];
            }
        }
    }
    bool connected(int u, int v) { return find(u) == find(v); }
};
DSU dsu;
const int dir[5]{0, 1, 0, -1, 0};
const int dir2[9]{0, 1, 1, -1, 1, 0, -1, -1, 0};

class Solution {
   public:
    int maximumSafenessFactor(vector<vector<int>>& grid) {
        int n = grid.size();
        if (n == 1) {
            return 0;
        }
        dsu.init(n * n);
        int s = 0;
        int t = n * n - 1;
        for (int i = 1; i < n; i++) {
            dsu.unite(s, i * n);
            dsu.unite(t, (i - 1) * n + n - 1);
        }
        for (int j = 1; j < n - 1; j++) {
            dsu.unite(s, (n - 1) * n + j);
            dsu.unite(t, j);
        }
        int l = 0;
        int r = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j]) {
                    if (i == 0 && j == 0) {
                        return 0;
                    }
                    if (i == n - 1 && j == n - 1) {
                        return 0;
                    }
                    q[r++] = {i, j, 1};
                    for (int k = 0; k < 8; k++) {
                        int x = i + dir2[k];
                        int y = j + dir2[k + 1];
                        if (x < 0 || y < 0 || x >= n || y >= n) {
                            continue;
                        }
                        if (grid[x][y]) {
                            dsu.unite(x * n + y, i * n + j);
                        }
                    }
                }
            }
        }
        if (dsu.connected(s, t)) {
            return 0;
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
                if (x == 0 && y == 0) {
                    return u.d;
                }
                if (x == n - 1 && y == n - 1) {
                    return u.d;
                }
                grid[x][y] = 1;
                q[r++] = {x, y, u.d + 1};
                for (int k2 = 0; k2 < 8; k2++) {
                    int x2 = x + dir2[k2];
                    int y2 = y + dir2[k2 + 1];
                    if (x2 < 0 || y2 < 0 || x2 >= n || y2 >= n) {
                        continue;
                    }
                    if (grid[x2][y2]) {
                        dsu.unite(x * n + y, x2 * n + y2);
                    }
                }
            }
            if (dsu.connected(s, t)) {
                return u.d;
            }
        }
        return 0;
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