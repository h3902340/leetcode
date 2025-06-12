#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class Solution {
   public:
    long long minCost(int n, vector<vector<int>>& cost) {
        n >>= 1;
        vector<vector<long long>> dp(3, vector<long long>(3));
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (i == j) continue;
                dp[i][j] = cost[n - 1][i] + cost[n][j];
            }
        }
        vector<vector<long long>> tmp(3, vector<long long>(3));
        for (int k = 1; k < n; k++) {
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (i == j) continue;
                    long long c = cost[n - 1 - k][i] + cost[n + k][j];
                    long long d = -1;
                    for (int i2 = 0; i2 < 3; i2++) {
                        if (i == i2) continue;
                        for (int j2 = 0; j2 < 3; j2++) {
                            if (j == j2) continue;
                            if (i2 == j2) continue;
                            if (d == -1 || d > dp[i2][j2]) {
                                d = dp[i2][j2];
                            }
                        }
                    }
                    tmp[i][j] = c + d;
                }
            }
            swap(dp, tmp);
        }
        long long res = -1;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (i == j) continue;
                if (res == -1 || res > dp[i][j]) {
                    res = dp[i][j];
                }
            }
        }
        return res;
    }
};

int main() {
    string problemName = "3429";
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
        auto n = jread_int(line_in);
        getline(file_in, line_in);
        auto cost = jread_vector2d(line_in);
        auto res = sol.minCost(n, cost);
        getline(file_out, line_out);
        auto ans = jread_longlong(line_out);
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