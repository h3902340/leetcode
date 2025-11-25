#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int D = 3;
int dp[2][D];

class Solution {
   public:
    int maxSumDivThree(vector<int>& nums) {
        int n = nums.size();
        for (int i = 0; i < D; i++) {
            dp[0][i] = 0;
        }
        dp[0][nums[0] % D] = nums[0];
        bool p = false;
        for (int i = 1; i < n; i++) {
            p = !p;
            int r = nums[i] % D;
            for (int j = 0; j < D; j++) {
                int k = (j - r + D) % D;
                dp[p][j] = dp[!p][j];
                if (dp[!p][k] == 0) {
                    if (j == r) {
                        dp[p][j] = max(dp[p][j], nums[i]);
                    }
                } else {
                    dp[p][j] = max(dp[p][j], dp[!p][k] + nums[i]);
                }
            }
        }
        return dp[p][0];
    }
};

int main() {
    string problemName = "1262";
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
        auto res = sol.maxSumDivThree(nums);
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