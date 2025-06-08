#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

// same as LC 123
const int N = 1e5;
const int K = 1e2;
int dp[N][K + 1];

class Solution {
   public:
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        for (int i = 0; i < n; i++) {
            dp[i][0] = 0;
        }
        for (int j = 0; j <= k; j++) {
            dp[0][j] = 0;
        }
        for (int j = 1; j <= k; j++) {
            int mx = INT32_MIN;
            for (int i = 1; i < n; i++) {
                int a = dp[i - 1][j - 1] - prices[i - 1];
                if (mx < a) {
                    mx = a;
                }
                dp[i][j] = max(dp[i - 1][j], prices[i] + mx);
            }
        }
        return dp[n - 1][k];
    }
};

int main() {
    string problemName = "188";
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
        auto k = jread_int(line_in);
        getline(file_in, line_in);
        auto prices = jread_vector(line_in);
        auto res = sol.maxProfit(k, prices);
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