#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int N = 200;
int dp[N + 1][N + 1];
bool isInit = false;
static void init() {
    for (int i = 0; i <= N; i++) {
        for (int j = 0; j <= N; j++) {
            dp[i][j] = INT32_MAX;
        }
    }
    for (int i = 1; i < N; i++) {
        dp[i][i] = 0;
        dp[i][i + 1] = i;
    }
    dp[N][N] = 0;
    for (int l = 2; l <= N; l++) {
        for (int i = 1; i + l <= N; i++) {
            for (int j = i + 1; j <= i + l - 1; j++) {
                int a = j + max(dp[i][j - 1], dp[j + 1][i + l]);
                if (dp[i][i + l] > a) {
                    dp[i][i + l] = a;
                }
            }
        }
    }
}
class Solution {
   public:
    int getMoneyAmount(int n) {
        if (!isInit) {
            init();
            isInit = true;
        }
        return dp[1][n];
    }
};

int main() {
    string problemName = "375";
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
        auto res = sol.getMoneyAmount(n);
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