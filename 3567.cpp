#include <set>
#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int KMAX = 30;
int arr[KMAX * KMAX];

class Solution {
   public:
    vector<vector<int>> minAbsDiff(vector<vector<int>>& grid, int k) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> res(m - k + 1, vector<int>(n - k + 1, 0));
        if (k == 1) {
            return res;
        }
        for (int x = 0; x < m - k + 1; x++) {
            for (int y = 0; y < n - k + 1; y++) {
                int t = 0;
                for (int i = 0; i < k; i++) {
                    for (int j = 0; j < k; j++) {
                        arr[t++] = grid[x + i][y + j];
                    }
                }
                sort(begin(arr), begin(arr) + t);
                int pre = arr[0];
                int min = INT32_MAX;
                for (int i = 1; i < t; i++) {
                    if (arr[i] == pre) {
                        continue;
                    }
                    int diff = arr[i] - pre;
                    if (min > diff) {
                        min = diff;
                    }
                    pre = arr[i];
                }
                if (pre == arr[0]) {
                    res[x][y] = 0;
                } else {
                    res[x][y] = min;
                }
            }
        }
        return res;
    }
};

int main() {
    string problemName = "3567";
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
        auto grid = jread_vector2d(line_in);
        getline(file_in, line_in);
        auto k = jread_int(line_in);
        auto res = sol.minAbsDiff(grid, k);
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