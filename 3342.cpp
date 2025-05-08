#include <queue>
#include <vector>
using namespace std;

struct Position {
    int i;
    int j;
    int v;
    int m;
};
const int dirLen = 4;
int dir[dirLen][2]{{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
class Solution {
   public:
    int minTimeToReach(vector<vector<int>>& moveTime) {
        int n = moveTime.size();
        int m = moveTime[0].size();
        auto cmp = [](Position left, Position right) {
            return left.v > right.v;
        };
        priority_queue<Position, vector<Position>, decltype(cmp)> pq(cmp);
        pq.push({0, 0, 0, 1});
        moveTime[0][0] = -1;
        while (true) {
            Position p = pq.top();
            pq.pop();
            for (int i = 0; i < dirLen; i++) {
                int x = p.i + dir[i][0];
                int y = p.j + dir[i][1];
                if (x < 0 || x >= n || y < 0 || y >= m) continue;
                int& v = moveTime[x][y];
                if (v != -1) {
                    int t = max(v, p.v) + p.m;
                    if (x == n - 1 && y == m - 1) {
                        return t;
                    }
                    pq.push({x, y, t, p.m ^ 3});
                    v = -1;
                }
            }
        }
        return -1;
    }
};

// 7
vector<vector<int>> moveTime = {{0, 4}, {4, 4}};

int main() {
    Solution sol;
    int ans = sol.minTimeToReach(moveTime);
    printf("ans = %d\n", ans);
    return 0;
}