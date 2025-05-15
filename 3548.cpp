#include <unordered_set>
#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

// TODO: Wrong Answer
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

int main() {
    string problemName = "3548";
    auto begin = jtimer();
    Solution sol;
    ifstream file_in("testcases/" + problemName + "_in.txt");
    ifstream file_out("testcases/" + problemName + "_out.txt");
    bool allPass = true;
    int caseCount = 0;
    int passCount = 0;
    string line_in1;
    string line_out;
    while (getline(file_in, line_in1)) {
        auto grid = jread_vector2d(line_in1);
        bool res = sol.canPartitionGrid(grid);
        getline(file_out, line_out);
        bool ans = jread_int(line_out);
        printf("Case %d", ++caseCount);
        if (res == ans) {
            passCount++;
            printf(" %s(PASS)", KGRN);
        } else {
            printf(" %s(WRONG)", KRED);
            allPass = false;
        }
        printf("\n%s", KNRM);
        // printf("grid = %s\n", line_in1.c_str());
        jprint_int(res, "res");
        jprint_int(ans, "ans");
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