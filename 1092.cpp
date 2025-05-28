#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

struct Node {
    char c;
    int prei;
    int prej;
    int len;
};
const int NMAX = 1000;
Node dp[NMAX][NMAX];

class Solution {
   public:
    string shortestCommonSupersequence(string str1, string str2) {
        int n = str1.size();
        int m = str2.size();
        bool has = false;
        for (int i = 0; i < n; i++) {
            has |= str1[i] == str2[0];
            if (has) {
                dp[i][0].c = str2[0];
                dp[i][0].prei = -1;
                dp[i][0].prej = -1;
                dp[i][0].len = 1;
            } else {
                dp[i][0].c = 0;
                dp[i][0].prei = -1;
                dp[i][0].prej = -1;
                dp[i][0].len = 0;
            }
        }
        has = false;
        for (int j = 0; j < m; j++) {
            has |= str1[0] == str2[j];
            if (has) {
                dp[0][j].c = str1[0];
                dp[0][j].prei = -1;
                dp[0][j].prej = -1;
                dp[0][j].len = 1;
            } else {
                dp[0][j].c = 0;
                dp[0][j].prei = -1;
                dp[0][j].prej = -1;
                dp[0][j].len = 0;
            }
        }
        for (int i = 1; i < n; i++) {
            for (int j = 1; j < m; j++) {
                if (str1[i] == str2[j]) {
                    dp[i][j].c = str1[i];
                    dp[i][j].prei = i - 1;
                    dp[i][j].prej = j - 1;
                    dp[i][j].len = dp[i - 1][j - 1].len + 1;
                } else {
                    if (dp[i][j - 1].len > dp[i - 1][j].len) {
                        dp[i][j].c = dp[i][j - 1].c;
                        dp[i][j].prei = dp[i][j - 1].prei;
                        dp[i][j].prej = dp[i][j - 1].prej;
                        dp[i][j].len = dp[i][j - 1].len;
                    } else {
                        dp[i][j].c = dp[i - 1][j].c;
                        dp[i][j].prei = dp[i - 1][j].prei;
                        dp[i][j].prej = dp[i - 1][j].prej;
                        dp[i][j].len = dp[i - 1][j].len;
                    }
                }
            }
        }
        Node lcs = dp[n - 1][m - 1];
        int l = lcs.len;
        int totalLen = n + m - l;
        string res(totalLen, 0);
        int x = n - 1;
        int y = m - 1;
        int z = totalLen - 1;
        while (lcs.len != 0) {
            while (str1[x] != lcs.c) {
                res[z--] = str1[x--];
            }
            x--;
            while (str2[y] != lcs.c) {
                res[z--] = str2[y--];
            }
            y--;
            res[z--] = lcs.c;
            if (lcs.prei == -1) break;
            lcs = dp[lcs.prei][lcs.prej];
        }
        while (x >= 0) {
            res[z--] = str1[x--];
        }
        while (y >= 0) {
            res[z--] = str2[y--];
        }
        return res;
    }
};

int main() {
    string problemName = "1092";
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
        auto str1 = jread_string(line_in);
        getline(file_in, line_in);
        auto str2 = jread_string(line_in);
        auto res = sol.shortestCommonSupersequence(str1, str2);
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
        jprint_string(str1, "str1");
        jprint_string(str2, "str2");
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