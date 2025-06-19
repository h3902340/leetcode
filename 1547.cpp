#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int M = 100;
int dp[M + 1][M + 1];
class Solution {
   public:
    int minCost(int n, vector<int>& cuts) {
        int m = cuts.size();
        cuts.push_back(0);
        cuts.push_back(n);
        sort(cuts.begin(), cuts.end());
        for (int i = 1; i <= m; i++) {
            dp[i][i] = cuts[i + 1] - cuts[i - 1];
        }
        for (int l = 1; l <= m; l++) {
            for (int i = 1; i + l <= m; i++) {
                dp[i][i + l] = INT32_MAX;
                for (int j = i; j <= i + l; j++) {
                    int a = cuts[i + l + 1] - cuts[i - 1];
                    if (i <= j - 1) {
                        a += dp[i][j - 1];
                    }
                    if (j + 1 <= i + l) {
                        a += dp[j + 1][i + l];
                    }
                    if (dp[i][i + l] > a) {
                        dp[i][i + l] = a;
                    }
                }
            }
        }
        return dp[1][m];
    }
};

int main() {
    string problemName = "1547";
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
        auto n = jread_int(line_in);
        getline(file_in, line_in);
        auto cuts = jread_vector(line_in);
        auto res = sol.minCost(n, cuts);
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