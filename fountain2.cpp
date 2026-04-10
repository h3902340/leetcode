#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct Data {
    int i;
    int j;
};
const int dir[5] = {0, 1, 0, -1, 0};
vector<vector<bool>> solve(vector<vector<int>>& height,
                           vector<vector<int>>& fountain) {
    int m = height.size();
    int n = height[0].size();
    int l = fountain.size();

    vector<vector<bool>> res(m, vector<bool>(n, false));
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

void test(vector<vector<int>>& height, vector<vector<int>>& fountain,
          vector<vector<bool>>& ans) {
    vector<vector<bool>> res = solve(height, fountain);
    cout << "res:[\n";
    for (size_t i = 0; i < res.size(); i++) {
        cout << "[";
        for (size_t j = 0; j < res[i].size(); j++) {
            cout << (res[i][j] ? 1 : 0) << ',';
        }
        cout << "]\n";
    }
    cout << "]\n";
    cout << "ans:[\n";
    for (size_t i = 0; i < ans.size(); i++) {
        cout << "[";
        for (size_t j = 0; j < ans[i].size(); j++) {
            cout << (ans[i][j] ? 1 : 0) << ',';
        }
        cout << "]\n";
    }
    cout << "]\n";
}

int main() {
    // test1
    vector<vector<int>> height = {
        {1, 3, 1, 1}, {3, 3, 1, 1}, {1, 1, 2, 1}, {1, 1, 1, 2}};
    vector<vector<int>> fountain = {{3, 3}};
    vector<vector<bool>> ans = {
        {0, 0, 1, 1}, {0, 0, 1, 1}, {1, 1, 0, 1}, {1, 1, 1, 0}};
    test(height, fountain, ans);
    // test2
    height = {{1, 3, 1, 1}, {3, 3, 1, 1}, {1, 1, 2, 1}, {1, 1, 1, 4}};
    fountain = {{0, 0}, {3, 3}};
    ans = {{1, 1, 1, 1}, {1, 1, 1, 1}, {1, 1, 1, 1}, {1, 1, 1, 0}};
    test(height, fountain, ans);
    // test3
    height = {{1, 5, 1, 2}, {3, 3, 5, 5}, {1, 1, 2, 1}, {1, 1, 1, 4}};
    fountain = {{0, 0}, {3, 3}, {0, 3}};
    ans = {{1, 0, 1, 1}, {1, 1, 0, 0}, {1, 1, 1, 1}, {1, 1, 1, 0}};
    test(height, fountain, ans);
}
