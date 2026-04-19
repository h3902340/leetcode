#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

struct Data {
    int i;
    int j;
    int k;
    int t;
};
const int dir[5]{0, 1, 0, -1, 0};
class Solution {
   public:
    vector<vector<int>> colorGrid(int n, int m, vector<vector<int>>& sources) {
        vector<vector<int>> res(n, vector<int>(m));
        vector<vector<int>> vis(n, vector<int>(m));
        queue<Data> q;
        for (auto& e : sources) {
            q.push({e[0], e[1], e[2], 2});
            res[e[0]][e[1]] = e[2];
            vis[e[0]][e[1]] = 1;
        }
        while (!q.empty()) {
            Data u = q.front();
            q.pop();
            for (int i = 0; i < 4; i++) {
                int x = u.i + dir[i];
                int y = u.j + dir[i + 1];
                if (x < 0 || y < 0 || x >= n || y >= m) {
                    continue;
                }
                if (vis[x][y] == 0) {
                    res[x][y] = u.k;
                } else if (vis[x][y] == u.t && res[x][y] < u.k) {
                    res[x][y] = u.k;
                } else {
                    continue;
                }
                vis[x][y] = u.t;
                q.push({x, y, u.k, u.t + 1});
            }
        }
        return res;
    }
};

int main() {
    string problemName = "3905";
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
        auto n = jread_int(line_in);
        getline(file_in, line_in);
        auto m = jread_int(line_in);
        getline(file_in, line_in);
        auto sources = jread_vector2d(line_in);
        auto res = sol.colorGrid(n, m, sources);
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