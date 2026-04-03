#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

struct Data {
    int i;
    int j;
};
int dp[1 << 8];
class Solution {
   public:
    int minimumMoves(vector<vector<int>>& grid) {
        vector<Data> a;
        vector<Data> b;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                for (int k = 1; k < grid[i][j]; k++) {
                    a.push_back({i, j});
                }
                if (grid[i][j] == 0) {
                    b.push_back({i, j});
                }
            }
        }
        int k = a.size();
        int l = 1 << k;
        dp[0] = 0;
        for (int i = 1; i < l; i++) {
            dp[i] = INT32_MAX;
            int c = __builtin_popcount(i);
            for (int j = 0; j < k; j++) {
                if (i & (1 << j)) {
                    dp[i] =
                        min(dp[i], dp[i ^ (1 << j)] + abs(a[j].i - b[c - 1].i) +
                                       abs(a[j].j - b[c - 1].j));
                }
            }
        }
        return dp[l - 1];
    }
};

int main() {
    string problemName = "2850";
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
        auto res = sol.minimumMoves(grid);
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