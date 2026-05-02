#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int N = 1e4;
int dp[N + 1];
int dg[5];
bool isInit = false;
void init() {
    dp[0] = 0;
    for (int i = 1; i <= N; i++) {
        int j = 0;
        int a = i;
        while (a > 0) {
            dg[j++] = a % 10;
            a /= 10;
        }
        bool ok = false;
        for (int k = 0; k < j; k++) {
            if (dg[k] == 3 || dg[k] == 4 || dg[k] == 7) {
                ok = false;
                break;
            }
            if (dg[k] == 2 || dg[k] == 5 || dg[k] == 6 || dg[k] == 9) {
                ok = true;
            }
        }
        dp[i] = ok + dp[i - 1];
    }
}
class Solution {
public:
    int rotatedDigits(int n) {
        if (!isInit) {
            init();
            isInit = true;
        }
        return dp[n];
    }
};

int main() {
    string problemName = "788";
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
        auto res = sol.rotatedDigits(n);
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