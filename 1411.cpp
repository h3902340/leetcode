#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define ll long long
const int N = 5000;
const int MOD = 1e9 + 7;
int dp[2][N];
bool isInit = false;
int add(int a, int b) {
    a += b;
    if (a >= MOD) {
        a -= MOD;
    }
    return a;
}
void init() {
    dp[0][0] = 6;  // ABA: BAB,BCB,CAC,BAC,CAB
    dp[1][0] = 6;  // ABC: BAB,BCB,BCA,CAB
    for (int i = 1; i < N; i++) {
        int a = add(dp[0][i - 1], dp[1][i - 1]);
        a = add(a, a);
        dp[1][i] = a;
        dp[0][i] = add(a, dp[0][i - 1]);
        dp[0][i - 1] = add(dp[0][i - 1], dp[1][i - 1]);
    }
    dp[0][N - 1] = add(dp[0][N - 1], dp[1][N - 1]);
}

class Solution {
   public:
    int numOfWays(int n) {
        if (!isInit) {
            init();
            isInit = true;
        }
        return dp[0][n - 1];
    }
};

int main() {
    string problemName = "1411";
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
        auto res = sol.numOfWays(n);
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