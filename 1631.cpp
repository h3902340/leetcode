#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

struct Data {
    int x;
    int y;
    int w;
    bool operator>(const Data& a) const { return w > a.w; }
};
const int R = 100;
const int C = 100;
const int DIR[5] = {0, 1, 0, -1, 0};
int dis[R][C];
bool vis[R][C];

class Solution {
   public:
    int minimumEffortPath(vector<vector<int>>& heights) {
        int r = heights.size();
        int c = heights[0].size();
        priority_queue<Data, vector<Data>, greater<Data>> pq;
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                dis[i][j] = -1;
                vis[i][j] = false;
            }
        }
        dis[0][0] = 0;
        pq.push({0, 0, 0});
        int res = -1;
        while (!pq.empty()) {
            Data t = pq.top();
            pq.pop();
            if (vis[t.x][t.y]) {
                continue;
            }
            if (t.x == r - 1 && t.y == c - 1) {
                return dis[t.x][t.y];
            }
            vis[t.x][t.y] = true;
            for (int i = 0; i < 4; i++) {
                int x = t.x + DIR[i];
                int y = t.y + DIR[i + 1];
                if (x < 0 || x >= r || y < 0 || y >= c) {
                    continue;
                }
                int w = abs(heights[x][y] - heights[t.x][t.y]);
                int a = max(t.w, w);
                if (dis[x][y] == -1 || dis[x][y] > a) {
                    dis[x][y] = a;
                    pq.push({x, y, a});
                }
            }
        }
        return dis[r - 1][c - 1];
    }
};

int main() {
    string problemName = "1631";
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
        auto res = sol.minimumEffortPath(heights);
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