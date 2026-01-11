#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int M = 1000;
int dp[2][M];
int pre1[M];
int pre2[M];

class Solution {
   public:
    int minimumDeleteSum(string s1, string s2) {
        int m = s1.size();
        int n = s2.size();
        pre1[0] = s1[0];
        pre2[0] = s2[0];
        for (int i = 1; i < m; i++) {
            pre1[i] = pre1[i - 1] + s1[i];
        }
        for (int j = 1; j < n; j++) {
            pre2[j] = pre2[j - 1] + s2[j];
        }
        bool p = 1;
        bool q = 0;
        for (int j = 0; j < n; j++) {
            for (int i = 0; i < m; i++) {
                if (s1[i] == s2[j]) {
                    if (i == 0) {
                        if (j == 0) {
                            dp[p][i] = 0;
                        } else {
                            dp[p][i] = pre2[j - 1];
                        }
                    } else {
                        if (j == 0) {
                            dp[p][i] = pre1[i - 1];
                        } else {
                            dp[p][i] = dp[q][i - 1];
                        }
                    }
                } else {
                    if (i == 0) {
                        dp[p][i] = pre2[j] + s1[i];
                    } else {
                        dp[p][i] = dp[p][i - 1] + s1[i];
                    }
                    if (j == 0) {
                        dp[p][i] = min(dp[p][i], pre1[i] + s2[j]);
                    } else {
                        dp[p][i] = min(dp[p][i], dp[q][i] + s2[j]);
                    }
                }
            }
            swap(p, q);
        }
        return dp[q][m - 1];
    }
};

int main() {
    string problemName = "712";
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
        auto s1 = jread_string(line_in);
        getline(file_in, line_in);
        auto s2 = jread_string(line_in);
        auto res = sol.minimumDeleteSum(s1, s2);
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