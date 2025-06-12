#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int NMAX = 1e3;
int maxSubStr[NMAX];
int sPal[NMAX];
int tPal[NMAX];
bool dp[NMAX][NMAX];

class Solution {
   public:
    int longestPalindrome(string s, string t) {
        reverse(t.begin(), t.end());
        int n = s.size();
        int m = t.size();
        calcPal(s, n, sPal);
        calcPal(t, m, tPal);
        int res = 0;
        for (int j = 0; j < m; j++) {
            int tmp = 2;
            if (s[0] == t[j]) {
                maxSubStr[j] = 1;
                if (1 < n && j + 1 < m) {
                    tmp += max(sPal[1], tPal[j + 1]);
                } else if (1 < n) {
                    tmp += sPal[1];
                } else if (j + 1 < m) {
                    tmp += tPal[j + 1];
                }
            } else {
                maxSubStr[j] = 0;
                tmp = max(sPal[0], tPal[j]);
            }
            if (res < tmp) {
                res = tmp;
            }
        }
        for (int i = 1; i < n; i++) {
            int tmp = 0;
            for (int j = m - 1; j >= 1; j--) {
                if (s[i] == t[j]) {
                    maxSubStr[j] = maxSubStr[j - 1] + 1;
                    tmp = maxSubStr[j] * 2;
                    if (i + 1 < n && j + 1 < m) {
                        tmp += max(sPal[i + 1], tPal[j + 1]);
                    } else if (i + 1 < n) {
                        tmp += sPal[i + 1];
                    } else if (j + 1 < m) {
                        tmp += tPal[j + 1];
                    }
                } else {
                    maxSubStr[j] = 0;
                    tmp = max(sPal[i], tPal[j]);
                }
                if (res < tmp) {
                    res = tmp;
                }
            }
            tmp = 2;
            if (s[i] == t[0]) {
                maxSubStr[0] = 1;
                if (i + 1 < n && 1 < m) {
                    tmp += max(sPal[i + 1], tPal[1]);
                } else if (i + 1 < n) {
                    tmp += sPal[i + 1];
                } else if (1 < m) {
                    tmp += tPal[1];
                }
            } else {
                maxSubStr[0] = 0;
                tmp = max(sPal[i], tPal[0]);
            }
            if (res < tmp) {
                res = tmp;
            }
        }
        return res;
    }

   private:
    void calcPal(string s, int n, int pal[NMAX]) {
        for (int i = 0; i < n; i++) {
            dp[i][i] = 1;
        }
        for (int i = 1; i < n; i++) {
            if (s[i - 1] == s[i]) {
                dp[i - 1][i] = 1;
            } else {
                dp[i - 1][i] = 0;
            }
        }
        for (int len = 3; len <= n; len++) {
            for (int i = 0; i <= n - len; i++) {
                int j = i + len - 1;
                if (s[i] == s[j]) {
                    dp[i][j] = dp[i + 1][j - 1];
                } else {
                    dp[i][j] = 0;
                }
            }
        }
        for (int i = 0; i < n; i++) {
            int maxj = 0;
            for (int j = i; j < n; j++) {
                if (dp[i][j]) {
                    maxj = j;
                }
            }
            pal[i] = maxj - i + 1;
        }
    }
};

int main() {
    string problemName = "3504";
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
        getline(file_in, line_in);
        auto t = jread_string(line_in);
        auto res = sol.longestPalindrome(s, t);
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