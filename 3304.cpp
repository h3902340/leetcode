#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int C = 26;
bool isInit = false;
const int K = 500;
char dp[K + 1];
static void init() {
    if (isInit) return;
    dp[1] = 'a';
    int m = 1;
    int i = 2;
    while (i <= K) {
        int cap = min(m << 1, K);
        for (; i <= cap; i++) {
            dp[i] = dp[i - m] + 1;
            if (dp[i] > 'z') {
                dp[i] -= C;
            }
        }
        m <<= 1;
    }
    isInit = true;
}

class Solution {
   public:
    char kthCharacter(int k) {
        init();
        return dp[k];
    }
};

int main() {
    string problemName = "3304";
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
        auto res = sol.kthCharacter(k);
        getline(file_out, line_out);
        auto ans = jread_char(line_out);
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