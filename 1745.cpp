#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int N = 2000;
bool dp[N][N];
class Solution {
   public:
    bool checkPartitioning(string s) {
        int n = s.size();
        dp[0][0] = true;
        for (int i = 1; i < n; i++) {
            dp[i][i] = true;
            dp[i - 1][i] = s[i - 1] == s[i];
        }
        for (int l = 2; l < n; l++) {
            for (int i = 0; i + l < n; i++) {
                dp[i][i + l] = s[i] == s[i + l] && dp[i + 1][i + l - 1];
            }
        }
        for (int i = 0; i < n - 2; i++) {
            for (int j = n - 1; j > i + 1; j--) {
                if (dp[0][i] && dp[i + 1][j - 1] && dp[j][n - 1]) {
                    return true;
                }
            }
        }
        return false;
    }
};

int main() {
    string problemName = "1745";
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
        auto s = jread_string(line_in);
        auto res = sol.checkPartitioning(s);
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