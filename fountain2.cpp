#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

struct Data {
    int i;
    int j;
};
const int dir[5] = {0, 1, 0, -1, 0};
class Solution {
   public:
    vector<vector<int>> solve(vector<vector<int>>& height,
                              vector<vector<int>>& fountain) {
        int m = height.size();
        int n = height[0].size();
        int l = fountain.size();
        jprint(height, "height");
        jprint(fountain, "fountain");
        vector<vector<int>> res(m, vector<int>(n, 0));
        vector<vector<int>> src(m, vector<int>(n, -1));
        vector<int> par(l, -1);
        queue<Data> q;
        for (int i = 0; i < l; i++) {
            int x = fountain[i][0];
            int y = fountain[i][1];
            q.push({x, y});
            src[x][y] = i;
            while (!q.empty()) {
                Data u = q.front();
                q.pop();
                for (int k = 0; k < 4; k++) {
                    int x2 = u.i + dir[k];
                    int y2 = u.j + dir[k + 1];
                    if (x2 < 0 || y2 < 0 || x2 >= m || y2 >= n) {
                        continue;
                    }
                    if (height[x2][y2] <= height[x][y]) {
                        if (src[x2][y2] != -1) {
                            if (src[x2][y2] != i) {
                                par[i] = src[x2][y2];
                            }
                            continue;
                        }
                        q.push({x2, y2});
                        src[x2][y2] = i;
                    }
                }
            }
        }
        vector<bool> isRoot(l, false);
        vector<bool> check(l, false);
        for (int i = 0; i < l; i++) {
            if (check[i]) {
                continue;
            }
            int x = fountain[i][0];
            int y = fountain[i][1];
            int t = i;
            int s = i;
            int mx = height[x][y];
            while (par[t] != -1) {
                check[t] = true;
                t = par[t];
                x = fountain[t][0];
                y = fountain[t][1];
                mx = max(mx, height[x][y]);
            }
            check[t] = true;
            while (par[s] != -1) {
                int a = par[s];
                par[s] = t;
                s = a;
            }
            x = fountain[t][0];
            y = fountain[t][1];
            if (height[x][y] < mx) {
                res[x][y] = true;
            }
            height[x][y] = mx;
            isRoot[t] = true;
        }
        vector<vector<bool>> vis(m, vector<bool>(n, false));
        for (int i = 0; i < l; i++) {
            if (!isRoot[i]) {
                continue;
            }
            int x = fountain[i][0];
            int y = fountain[i][1];
            q.push({x, y});
            vis[x][y] = true;
            while (!q.empty()) {
                Data u = q.front();
                q.pop();
                for (int k = 0; k < 4; k++) {
                    int x2 = u.i + dir[k];
                    int y2 = u.j + dir[k + 1];
                    if (x2 < 0 || y2 < 0 || x2 >= m || y2 >= n) {
                        continue;
                    }
                    if (vis[x2][y2]) {
                        continue;
                    }
                    vis[x2][y2] = true;
                    if (height[x2][y2] <= height[x][y]) {
                        if (height[x2][y2] < height[x][y]) {
                            res[x2][y2] = true;
                        }
                        q.push({x2, y2});
                    }
                }
            }
        }
        return res;
    }
};

int main() {
    string problemName = "fountain2";
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
        auto height = jread_vector2d(line_in);
        getline(file_in, line_in);
        auto fountain = jread_vector2d(line_in);
        auto res = sol.solve(height, fountain);
        getline(file_out, line_out);
        auto ans = jread_vector2d(line_out);
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