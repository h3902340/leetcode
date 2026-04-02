#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int M = 500;
const int N = 500;
int dp[2][N][3];
class Solution {
   public:
    int maximumAmount(vector<vector<int>>& coins) {
        int m = coins.size();
        int n = coins[0].size();
        int p = 0;
        int q = 1;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < 3; k++) {
                    dp[q][j][k] = INT32_MIN;
                    for (int l = 0; l <= k; l++) {
                        int a = i == 0 ? INT32_MIN : dp[p][j][l];
                        int b = j == 0 ? INT32_MIN : dp[q][j - 1][l];
                        int c = i == 0 && j == 0 ? 0 : max(a, b);
                        if (coins[i][j] >= 0 || k == l) {
                            c += coins[i][j];
                        }
                        dp[q][j][k] = max(dp[q][j][k], c);
                    }
                }
            }
            swap(p, q);
        }
        return dp[p][n - 1][2];
    }
};

int main() {
    string problemName = "3418";
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
        auto coins = jread_vector2d(line_in);
        auto res = sol.maximumAmount(coins);
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