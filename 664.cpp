#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int N = 100;
int dp[N][N];
class Solution {
   public:
    int strangePrinter(string s) {
        int n = s.size();
        for (int i = 0; i < n; i++) {
            dp[i][i] = 1;
        }
        for (int l = 1; l < n; l++) {
            for (int i = 0; i + l < n; i++) {
                int a = 1 + dp[i + 1][i + l];
                for (int j = i + 1; j <= i + l; j++) {
                    if (s[i] == s[j]) {
                        // if a.....a, then printing "a" from start to end is
                        // optimal
                        int b = dp[i][j - 1];
                        if (j + 1 <= i + l) {
                            b += dp[j + 1][i + l];
                        }
                        if (a > b) {
                            a = b;
                        }
                    }
                }
                dp[i][i + l] = a;
            }
        }
        return dp[0][n - 1];
    }
};

int main() {
    string problemName = "664";
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
        auto res = sol.strangePrinter(s);
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