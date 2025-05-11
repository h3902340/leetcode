#include <vector>
using namespace std;

class Solution {
   public:
    bool canPartitionGrid(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        long total = 0;
        vector<long> v(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                v[i] += grid[j][i];
            }
            total += v[i];
        }
        if (total & 1) return false;
        total >>= 1;
        long left = v[0];
        if (left == total) return true;
        for (int i = 1; i < n; i++) {
            left += v[i];
            if (left == total) return true;
            if (left > total) break;
        }

        vector<long> h(m);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                h[i] += grid[i][j];
            }
        }
        long top = h[0];
        if (top == total) return true;
        for (int i = 1; i < m; i++) {
            top += h[i];
            if (top == total) return true;
            if (top > total) break;
        }
        return false;
    }
};

// true
vector<vector<int>> grid = {{1, 4}, {2, 3}};

int main() {
    Solution sol;
    bool ans = sol.canPartitionGrid(grid);
    printf("ans = %s\n", ans ? "true" : "false");
    return 0;
}