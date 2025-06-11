#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int N = 1e3;
bool dp[N][N];

class Solution {
   public:
    string longestPalindrome(string s) {
        int n = s.size();
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                dp[i][j] = false;
            }
        }
        int imax = 0;
        int lmax = 0;
        for (int i = 0; i < n; i++) {
            dp[i][i] = true;
            if (i + 1 < n && s[i] == s[i + 1]) {
                dp[i][i + 1] = true;
                imax = i;
                lmax = 1;
            }
        }
        bool flags[2]{false};
        for (int l = 2; l < n; l++) {
            if (flags[0] && flags[1]) break;
            if (flags[l & 1]) continue;
            bool allFalse = true;
            for (int i = 0; i + l < n; i++) {
                if (s[i] == s[i + l] && dp[i + 1][i + l - 1]) {
                    dp[i][i + l] = true;
                    imax = i;
                    lmax = l;
                    allFalse = false;
                } else {
                    dp[i][i + l] = false;
                }
            }
            if (allFalse) {
                flags[l & 1] = true;
            }
        }
        return s.substr(imax, lmax + 1);
    }
};

int main() {
    string problemName = "5";
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
        auto res = sol.longestPalindrome(s);
        getline(file_out, line_out);
        auto ans = jread_string(line_out);
        printf("Case %d", ++caseCount);
        if (res == ans) {
            passCount++;
            printf(" %s(PASS)", KGRN);
        } else {
            printf(" %s(WRONG)", KRED);
            allPass = false;
        }
        printf("\n%s", KNRM);
        jprint_string(res, "res");
        jprint_string(ans, "ans");
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