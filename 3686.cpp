#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int MOD = 1e9 + 7;
int dp[2][3];
class Solution {
   public:
    int countStableSubsequences(vector<int>& nums) {
        int n = nums.size();
        for (int j = 0; j < 2; j++) {
            dp[j][0] = 1;
            for (int k = 1; k < 3; k++) {
                dp[j][k] = 0;
            }
        }
        for (int i = 0; i < n; i++) {
            int parity = nums[i] & 1;
            for (int k = 2; k >= 1; k--) {
                add(dp[parity][k], dp[parity][k - 1]);
                add(dp[parity][1], dp[!parity][k]);
            }
        }
        int res = 0;
        for (int j = 0; j < 2; j++) {
            for (int k = 2; k >= 1; k--) {
                add(res, dp[j][k]);
            }
        }
        return res;
    }
    void add(int& a, int b) {
        a += b;
        if (a >= MOD) {
            a -= MOD;
        }
    }
};

int main() {
    string problemName = "3686";
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
        auto res = sol.countStableSubsequences(nums);
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