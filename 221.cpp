#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int M = 300;
const int N = 300;
int dp[M][N];

class Solution {
   public:
    int maximalSquare(vector<vector<char>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        int res = 0;
        dp[0][0] = matrix[0][0] - '0';
        if (dp[0][0] == 1) {
            res = 1;
        }
        for (int i = 1; i < m; i++) {
            dp[i][0] = matrix[i][0] - '0';
            if (dp[i][0] == 1) {
                res = 1;
            }
        }
        for (int j = 1; j < n; j++) {
            dp[0][j] = matrix[0][j] - '0';
            if (dp[0][j] == 1) {
                res = 1;
            }
        }
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                if (matrix[i][j] == '0') {
                    dp[i][j] = 0;
                    continue;
                }
                int a = min(dp[i - 1][j], dp[i][j - 1]);
                a = min(a, dp[i - 1][j - 1]) + 1;
                dp[i][j] = a;
                res = max(res, a);
            }
        }
        return res * res;
    }
};

int main() {
    string problemName = "221";
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
        auto matrix = jread_vector2d_char(line_in);
        auto res = sol.maximalSquare(matrix);
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