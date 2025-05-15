#include <vector>
using namespace std;

// TODO: the code can be slightly faster, currently, it's 20 ms, beats 97.61%
const int NMAX = 1e5 + 1;
struct Range {
    int min = INT32_MAX;
    int max = 0;
};
Range h[NMAX];
Range v[NMAX];
class Solution {
   public:
    int countCoveredBuildings(int n, vector<vector<int>>& buildings) {
        for (int i = 0; i <= n; i++) {
            h[i].min = INT32_MAX;
            h[i].max = 0;
            v[i].min = INT32_MAX;
            v[i].max = 0;
        }
        for (int i = 0; i < buildings.size(); i++) {
            int x = buildings[i][0];
            int y = buildings[i][1];
            if (x < h[y].min) {
                h[y].min = x;
            }
            if (x > h[y].max) {
                h[y].max = x;
            }
            if (y < v[x].min) {
                v[x].min = y;
            }
            if (y > v[x].max) {
                v[x].max = y;
            }
        }
        int ans = 0;
        for (int i = 0; i < buildings.size(); i++) {
            int x = buildings[i][0];
            int y = buildings[i][1];
            if (x > h[y].min && x < h[y].max && y > v[x].min && y < v[x].max) {
                ans++;
            }
        }
        return ans;
    }
};

int n = 3;
vector<vector<int>> buildings = {{1, 2}, {2, 2}, {3, 2}, {2, 1}, {2, 3}};

int main() {
    Solution sol;
    int ans = sol.countCoveredBuildings(n, buildings);
    printf("ans = %d\n", ans);
    return 0;
}