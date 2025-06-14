#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int N = 2000;
bool dp[N][N];
int memo[N];
class Solution {
   public:
    int minCut(string s) {
        int n = s.size();
        memo[0] = -1;
        dp[0][0] = true;
        for (int i = 1; i < n; i++) {
            memo[i] = -1;
            dp[i][i] = true;
            if (s[i - 1] == s[i]) {
                dp[i - 1][i] = true;
            } else {
                dp[i - 1][i] = false;
            }
        }
        for (int l = 2; l < n; l++) {
            for (int i = 0; i + l < n; i++) {
                if (dp[i + 1][i + l - 1] && s[i] == s[i + l]) {
                    dp[i][i + l] = true;
                } else {
                    dp[i][i + l] = false;
                }
            }
        }
        return dfs(0, n);
    }
    int dfs(int i, int n) {
        if (i == n) {
            return 0;
        }
        if (dp[i][n - 1]) {
            return 0;
        }
        if (memo[i] != -1) {
            return memo[i];
        }
        int res = n - 1;
        for (int j = i; j < n; j++) {
            if (dp[i][j]) {
                int a = 1 + dfs(j + 1, n);
                if (res > a) {
                    res = a;
                }
            }
        }
        memo[i] = res;
        return res;
    }
};

int main() {
    string problemName = "132";
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
        auto res = sol.minCut(s);
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