#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

struct Node {
    char c;
    int next;
    int len;
};
const int NMAX = 250;
bool dp[NMAX][NMAX];
Node memo[NMAX + 1];
class Solution {
   public:
    string lexicographicallySmallestString(string s) {
        int n = s.size();
        runDP(s, n);
        memo[n].c = 0;
        memo[n].len = 0;
        for (int i = n - 1; i >= 0; i--) {
            if (dp[i][n - 1]) {
                memo[i].c = 0;
                memo[i].len = 0;
                continue;
            }
            char min = s[i];
            int mink = 0;
            int k = 2;
            while (i + k < n) {
                if (dp[i][i + k - 1] && s[i + k] < min) {
                    min = s[i + k];
                    mink = k;
                }
                k += 2;
            }
            memo[i].c = min;
            int minIndex = i + mink + 1;
            mink += 2;
            while (i + mink < n) {
                if (dp[i][i + mink - 1] && s[i + mink] == min) {
                    int pre = minIndex;
                    int cur = i + mink + 1;
                    int curOld = cur;
                    bool isSmaller = true;
                    while (memo[cur].c != 0) {
                        if (memo[pre].c == 0) {
                            isSmaller = false;
                            break;
                        }
                        if (memo[cur].c < memo[pre].c) {
                            isSmaller = true;
                            break;
                        }
                        if (memo[cur].c > memo[pre].c) {
                            isSmaller = false;
                            break;
                        }
                        pre = memo[pre].next;
                        cur = memo[cur].next;
                    }
                    if (isSmaller) {
                        minIndex = curOld;
                    }
                }
                mink += 2;
            }
            memo[i].next = minIndex;
            memo[i].len = memo[minIndex].len + 1;
        }
        string res(memo[0].len, 0);
        int i = 0;
        int j = 0;
        while (memo[i].c != 0) {
            res[j++] = memo[i].c;
            i = memo[i].next;
        }
        return res;
    }

   private:
    bool isConsecutive(char a, char b) {
        return abs(a - b) == 1 || abs(a - b) == 25;
    }
    void runDP(string s, int n) {
        for (int i = 0; i < n - 1; i++) {
            dp[i][i + 1] = isConsecutive(s[i], s[i + 1]);
        }
        for (int j = 3; j < n; j += 2) {
            for (int i = 0; i < n - j; i++) {
                dp[i][i + j] = false;
                if (isConsecutive(s[i], s[i + 1]) && dp[i + 2][i + j]) {
                    dp[i][i + j] = true;
                    continue;
                }
                if (isConsecutive(s[i], s[i + j]) && dp[i + 1][i + j - 1]) {
                    dp[i][i + j] = true;
                    continue;
                }
                for (int k = 3; k <= j - 2; k += 2) {
                    if (isConsecutive(s[i], s[i + k]) && dp[i + 1][i + k - 1] &&
                        dp[i + k + 1][i + j]) {
                        dp[i][i + j] = true;
                        break;
                    }
                }
            }
        }
    }
};

int main() {
    string problemName = "3561";
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
        auto res = sol.lexicographicallySmallestString(s);
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
        jprint_string(s, "s");
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