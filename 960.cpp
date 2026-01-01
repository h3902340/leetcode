#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

bool le(vector<string>& strs, int n, int a, int b) {
    for (int i = 0; i < n; i++) {
        if (strs[i][a] > strs[i][b]) {
            return false;
        }
    }
    return true;
}

const int M = 100;
int dp[M];

class Solution {
   public:
    int minDeletionSize(vector<string>& strs) {
        int n = strs.size();
        int m = strs[0].size();
        for (int i = 0; i < m; i++) {
            dp[i] = 1;
        }
        for (int i = 1; i < m; i++) {
            for (int j = i - 1; j >= 0; j--) {
                if (le(strs, n, j, i)) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
        }
        int res = 0;
        for (int i = 0; i < m; i++) {
            res = max(res, dp[i]);
        }
        return m - res;
    }
};

int main() {
    string problemName = "960";
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
        auto strs = jread_vector_string(line_in);
        auto res = sol.minDeletionSize(strs);
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