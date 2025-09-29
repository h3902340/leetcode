#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int N = 50;
int dp[N - 1][N];

class Solution {
   public:
    int minScoreTriangulation(vector<int>& v) {
        int n = v.size();
        int t = n - 1;
        for (int i = 1; i < t; i++) {
            for (int j = 0; j < n; j++) {
                dp[i][j] = INT32_MAX;
                int a = i + 1;
                for (int k = 1; k < a; k++) {
                    int b = dp[k - 1][j] +
                            v[j] * v[(j + k) % n] * v[(j + a) % n] +
                            dp[i - k][(j + k) % n];
                    if (dp[i][j] > b) {
                        dp[i][j] = b;
                    }
                }
            }
        }
        return dp[t - 1][0];
    }
};

int main() {
    string problemName = "1039";
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
        auto values = jread_vector(line_in);
        auto res = sol.minScoreTriangulation(values);
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