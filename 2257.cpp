#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class Solution {
   public:
    int countUnguarded(int m, int n, vector<vector<int>>& guards,
                       vector<vector<int>>& walls) {
        vector<vector<int>> grid(m, vector<int>(n, 0));
        for (auto& w : walls) {
            grid[w[0]][w[1]] = 1;
        }
        for (auto& g : guards) {
            grid[g[0]][g[1]] = 2;
        }
        int res = m * n - walls.size() - guards.size();
        for (int i = 0; i < m; i++) {
            int start = 0;
            bool isGuarded = false;
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 0) {
                    if (isGuarded) {
                        grid[i][j] = 3;
                        res--;
                        start = j + 1;
                    }
                    continue;
                }
                if (grid[i][j] == 1) {
                    start = j + 1;
                    isGuarded = false;
                    continue;
                }
                if (grid[i][j] == 2) {
                    for (int k = start; k < j; k++) {
                        grid[i][k] = 3;
                    }
                    res -= (j - start);
                    start = j + 1;
                    isGuarded = true;
                }
            }
        }
        for (int j = 0; j < n; j++) {
            int start = 0;
            bool isGuarded = false;
            for (int i = 0; i < m; i++) {
                if (grid[i][j] == 0) {
                    if (isGuarded) {
                        if (grid[i][j] != 3) {
                            grid[i][j] = 3;
                            res--;
                        }
                    }
                    continue;
                }
                if (grid[i][j] == 1) {
                    start = i + 1;
                    isGuarded = false;
                    continue;
                }
                if (grid[i][j] == 2) {
                    for (int k = start; k < i; k++) {
                        if (grid[k][j] != 3) {
                            grid[k][j] = 3;
                            res--;
                        }
                    }
                    start = i + 1;
                    isGuarded = true;
                }
            }
        }
        return res;
    }
};

int main() {
    string problemName = "2257";
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
        auto m = jread_int(line_in);
        getline(file_in, line_in);
        auto n = jread_int(line_in);
        getline(file_in, line_in);
        auto guards = jread_vector2d(line_in);
        getline(file_in, line_in);
        auto walls = jread_vector2d(line_in);
        auto res = sol.countUnguarded(m, n, guards, walls);
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