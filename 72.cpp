#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int N = 500;
int dp[2][N + 1];
class Solution {
   public:
    int minDistance(string word1, string word2) {
        int m = word1.size();
        int n = word2.size();
        for (int j = 0; j <= n; j++) {
            dp[0][j] = j;
        }
        int p = 0;
        int q = 1;
        for (int i = 1; i <= m; i++) {
            dp[q][0] = i;
            for (int j = 1; j <= n; j++) {
                int d = word1[i - 1] != word2[j - 1];
                dp[q][j] =
                    min({dp[p][j - 1] + d, dp[p][j] + 1, dp[q][j - 1] + 1});
            }
            swap(p, q);
        }
        return dp[p][n];
    }
};

int main() {
    string problemName = "72";
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
        auto word1 = jread_string(line_in);
        getline(file_in, line_in);
        auto word2 = jread_string(line_in);
        auto res = sol.minDistance(word1, word2);
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