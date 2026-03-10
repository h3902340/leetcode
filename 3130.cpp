#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int MOD = 1e9 + 7;
const int ZERO = 1000;
const int ONE = 1000;
int dp[ZERO + 1][ONE + 1][2];
int add(int a, int b) {
    a += b;
    if (a >= MOD) {
        a -= MOD;
    }
    return a;
}
int sub(int a, int b) {
    a -= b;
    if (a < 0) {
        a += MOD;
    }
    return a;
}

class Solution {
   public:
    int numberOfStableArrays(int zero, int one, int limit) {
        for (int i = zero; i > min(limit, zero); i--) {
            dp[i][0][0] = 0;
        }
        for (int i = min(limit, zero); i >= 1; i--) {
            dp[i][0][0] = 1;
        }
        for (int j = one; j > min(limit, one); j--) {
            dp[0][j][1] = 0;
        }
        for (int j = min(limit, one); j >= 1; j--) {
            dp[0][j][1] = 1;
        }
        for (int i = 1; i <= zero; i++) {
            for (int j = 1; j <= one; j++) {
                dp[i][j][0] = add(dp[i - 1][j][0], dp[i - 1][j][1]);
                dp[i][j][1] = add(dp[i][j - 1][0], dp[i][j - 1][1]);
                if (i - limit - 1 >= 0) {
                    dp[i][j][0] = sub(dp[i][j][0], dp[i - limit - 1][j][1]);
                }
                if (j - limit - 1 >= 0) {
                    dp[i][j][1] = sub(dp[i][j][1], dp[i][j - limit - 1][0]);
                }
            }
        }
        return add(dp[zero][one][0], dp[zero][one][1]);
    }
};

int main() {
    string problemName = "3130";
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
        auto zero = jread_int(line_in);
        getline(file_in, line_in);
        auto one = jread_int(line_in);
        getline(file_in, line_in);
        auto limit = jread_int(line_in);
        auto res = sol.numberOfStableArrays(zero, one, limit);
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