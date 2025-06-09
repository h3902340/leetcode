#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

// TODO: rolling DP
const int N = 1e3;
const int K = N >> 1;
// 0: nothing, 1: buy, 2: sell
long long dp[N][K + 1][3];

class Solution {
   public:
    long long maximumProfit(vector<int>& prices, int k) {
        int n = prices.size();
        for (int j = 0; j <= k; j++) {
            dp[0][j][0] = 0;
            dp[0][j][1] = -prices[0];
            dp[0][j][2] = prices[0];
        }
        for (int i = 1; i < n; i++) {
            dp[i][0][0] = 0;
            dp[i][0][1] = dp[i - 1][0][1];
            if (dp[i][0][1] < -prices[i]) {
                dp[i][0][1] = -prices[i];
            }
            dp[i][0][2] = dp[i - 1][0][2];
            if (dp[i][0][2] < prices[i]) {
                dp[i][0][2] = prices[i];
            }
        }
        for (int j = 1; j <= k; j++) {
            for (int i = 1; i < n; i++) {
                dp[i][j][0] = dp[i - 1][j][0];
                if (dp[i][j][0] < dp[i - 1][j - 1][1] + prices[i]) {
                    dp[i][j][0] = dp[i - 1][j - 1][1] + prices[i];
                }
                if (dp[i][j][0] < dp[i - 1][j - 1][2] - prices[i]) {
                    dp[i][j][0] = dp[i - 1][j - 1][2] - prices[i];
                }
                dp[i][j][1] = dp[i - 1][j][1];
                if (dp[i][j][1] < dp[i - 1][j][0] - prices[i]) {
                    dp[i][j][1] = dp[i - 1][j][0] - prices[i];
                }
                dp[i][j][2] = dp[i - 1][j][2];
                if (dp[i][j][2] < dp[i - 1][j][0] + prices[i]) {
                    dp[i][j][2] = dp[i - 1][j][0] + prices[i];
                }
            }
        }
        return dp[n - 1][k][0];
    }
};

int main() {
    string problemName = "3573";
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
        auto prices = jread_vector(line_in);
        getline(file_in, line_in);
        auto k = jread_int(line_in);
        auto res = sol.maximumProfit(prices, k);
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
        jprint_longlong(res, "res");
        jprint_longlong(ans, "ans");
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