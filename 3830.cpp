#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

int dp[3][2][2];

class Solution {
   public:
    int longestAlternating(vector<int>& nums) {
        int n = nums.size();
        dp[0][0][0] = 1;
        dp[0][1][0] = 1;
        dp[0][0][1] = 0;
        dp[0][1][1] = 0;
        int res = 1;
        if (nums[0] < nums[1]) {
            dp[1][0][0] = 2;
            dp[1][1][0] = 1;
            dp[1][0][1] = 1;
            dp[1][1][1] = 1;
            res = 2;
        } else if (nums[0] == nums[1]) {
            dp[1][0][0] = 1;
            dp[1][1][0] = 1;
            dp[1][0][1] = 1;
            dp[1][1][1] = 1;
        } else {
            dp[1][0][0] = 1;
            dp[1][1][0] = 2;
            dp[1][0][1] = 1;
            dp[1][1][1] = 1;
            res = 2;
        }
        for (int i = 2; i < n; i++) {
            dp[2][0][0] = 1;
            dp[2][1][0] = 1;
            dp[2][0][1] = 1;
            dp[2][1][1] = 1;
            if (nums[i - 1] < nums[i]) {
                dp[2][0][0] += dp[1][1][0];
                dp[2][0][1] += dp[1][1][1];
            } else if (nums[i - 1] > nums[i]) {
                dp[2][1][0] += dp[1][0][0];
                dp[2][1][1] += dp[1][0][1];
            }
            if (nums[i - 2] < nums[i]) {
                dp[2][0][1] = max(dp[2][0][1], dp[0][1][0] + 1);
            } else if (nums[i - 2] > nums[i]) {
                dp[2][1][1] = max(dp[2][1][1], dp[0][0][0] + 1);
            }
            for (int k = 0; k < 2; k++) {
                for (int l = 0; l < 2; l++) {
                    res = max(res, dp[2][k][l]);
                }
            }
            for (int j = 0; j < 2; j++) {
                for (int k = 0; k < 2; k++) {
                    for (int l = 0; l < 2; l++) {
                        dp[j][k][l] = dp[j + 1][k][l];
                    }
                }
            }
        }
        return res;
    }
};

int main() {
    string problemName = "3830";
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
        auto nums = jread_vector(line_in);
        auto res = sol.longestAlternating(nums);
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