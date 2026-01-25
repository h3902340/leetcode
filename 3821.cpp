#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define ll long long
const int D = 50;
ll dp[D][D + 1];
bool isInit = false;
void init() {
    dp[0][1] = 1;
    for (int i = 0; i < D; i++) {
        dp[i][0] = 1;
    }
    for (int i = 1; i < D; i++) {
        for (int j = 1; j <= i + 1; j++) {
            dp[i][j] = dp[i - 1][j] + dp[i - 1][j - 1];
        }
    }
}
class Solution {
   public:
    long long nthSmallest(long long n, int k) {
        if (!isInit) {
            init();
            isInit = true;
        }
        ll res = 0;
        while (k > 0) {
            int i = 0;
            while (n > dp[i][k]) {
                i++;
            }
            res |= (1LL << i);
            if (i == 0) {
                break;
            }
            n -= dp[i - 1][k];
            k--;
        }
        return res;
    }
};

int main() {
    string problemName = "3821";
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
        auto grid = jread_longlong(line_in);
        getline(file_in, line_in);
        auto k = jread_int(line_in);
        auto res = sol.nthSmallest(grid, k);
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