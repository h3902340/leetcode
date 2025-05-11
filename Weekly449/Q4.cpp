#include <unordered_set>
#include <vector>
using namespace std;

class Solution {
   public:
    bool canPartitionGrid(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        long target = 0;
        vector<long> v(n);
        vector<long> h(m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                target += grid[j][i];
            }
        }
        unordered_set<int> set;
        long left = 0;
        // left to right
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                v[i] += grid[j][i];
                set.insert(grid[j][i]);
            }
            left += v[i];
            if (left * 2 == target) return true;
            if (left * 2 > target) {
                if (i == 0) {
                    if (left * 2 - grid[0][0] == target) {
                        return true;
                    }
                    if (left * 2 - grid[m - 1][0] == target) {
                        return true;
                    }
                } else {
                    if (m == 1) {
                        if (left * 2 - grid[0][0] == target) {
                            return true;
                        }
                        if (left * 2 - grid[0][i] == target) {
                            return true;
                        }
                    } else {
                        if (set.count(left * 2 - target)) {
                            return true;
                        }
                    }
                }
            }
        }
        set.clear();
        // right to left
        long right = 0;
        for (int i = n - 1; i >= 0; i--) {
            for (int j = 0; j < m; j++) {
                set.insert(grid[j][i]);
            }
            right += v[i];
            if (right * 2 == target) return true;
            if (right * 2 > target) {
                if (i == n - 1) {
                    if (right * 2 - grid[0][n - 1] == target) {
                        return true;
                    }
                    if (right * 2 - grid[m - 1][n - 1] == target) {
                        return true;
                    }
                } else {
                    if (m == 1) {
                        if (right * 2 - grid[0][n - 1] == target) {
                            return true;
                        }
                        if (right * 2 - grid[0][i] == target) {
                            return true;
                        }
                    } else {
                        if (set.count(right * 2 - target)) {
                            return true;
                        }
                    }
                }
            }
        }
        set.clear();
        long top = 0;
        // top to bottom
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                h[i] += grid[i][j];
                set.insert(grid[i][j]);
            }
            top += h[i];
            if (top * 2 == target) return true;
            if (top * 2 > target) {
                if (i == 0) {
                    if (top * 2 - grid[0][0] == target) {
                        return true;
                    }
                    if (top * 2 - grid[0][n - 1] == target) {
                        return true;
                    }
                } else {
                    if (n == 1) {
                        if (top * 2 - grid[0][0] == target) {
                            return true;
                        }
                        if (top * 2 - grid[i][0] == target) {
                            return true;
                        }
                    } else {
                        if (set.count(top * 2 - target)) {
                            return true;
                        }
                    }
                }
            }
        }
        set.clear();
        // bottom to top
        long bottom = 0;
        for (int i = m - 1; i >= 0; i--) {
            for (int j = 0; j < n; j++) {
                set.insert(grid[i][j]);
            }
            bottom += h[i];
            if (bottom * 2 == target) return true;
            if (bottom * 2 > target) {
                if (i == m - 1) {
                    if (bottom * 2 - grid[m - 1][0] == target) {
                        return true;
                    }
                    if (bottom * 2 - grid[m - 1][n - 1] == target) {
                        return true;
                    }
                } else {
                    if (n == 1) {
                        if (bottom * 2 - grid[m - 1][0] == target) {
                            return true;
                        }
                        if (bottom * 2 - grid[i][0] == target) {
                            return true;
                        }
                    } else {
                        if (set.count(bottom * 2 - target)) {
                            return true;
                        }
                    }
                }
            }
        }
        return false;
    }
};

vector<vector<int>> grid = {{1, 2}, {3, 4}};

int main() {
    Solution sol;
    bool ans = sol.canPartitionGrid(grid);
    printf("ans = %s\n", ans ? "true" : "false");
    return 0;
}