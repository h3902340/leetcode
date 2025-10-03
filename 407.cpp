#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

struct Data {
    int v;
    int i;
    int j;
};
const int DIR[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
const auto cmp = [](Data& a, Data& b) { return a.v > b.v; };

class Solution {
   public:
    int trapRainWater(vector<vector<int>>& heightMap) {
        int m = heightMap.size();
        int n = heightMap[0].size();
        priority_queue<Data, vector<Data>, decltype(cmp)> pq(cmp);
        for (int i = 0; i < m; i++) {
            pq.push({heightMap[i][0], i, 0});
            pq.push({heightMap[i][n - 1], i, n - 1});
            heightMap[i][0] = -1;
            heightMap[i][n - 1] = -1;
        }
        for (int j = 1; j < n - 1; j++) {
            pq.push({heightMap[0][j], 0, j});
            pq.push({heightMap[m - 1][j], m - 1, j});
            heightMap[0][j] = -1;
            heightMap[m - 1][j] = -1;
        }
        int res = 0;
        while (!pq.empty()) {
            Data t = pq.top();
            pq.pop();
            for (auto& dir : DIR) {
                int x = t.i + dir[0];
                int y = t.j + dir[1];
                if (x < 0 || y < 0 || x >= m || y >= n) {
                    continue;
                }
                if (heightMap[x][y] == -1) {
                    continue;
                }
                if (heightMap[x][y] < t.v) {
                    res += t.v - heightMap[x][y];
                    pq.push({t.v, x, y});
                } else {
                    pq.push({heightMap[x][y], x, y});
                }
                heightMap[x][y] = -1;
            }
        }
        return res;
    }
};

int main() {
    string problemName = "407";
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
        auto heightMap = jread_vector2d(line_in);
        auto res = sol.trapRainWater(heightMap);
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