#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define ll long long
const int N = 1e5;
ll dp[3];

class Solution {
   public:
    long long minIncrementOperations(vector<int>& nums, int k) {
        int n = nums.size();
        for (int i = 0; i < 3; i++) {
            if (nums[i] < k) {
                dp[i] = k - nums[i];
            } else {
                dp[i] = 0;
            }
        }
        for (int i = 3; i < n; i++) {
            ll a = dp[0];
            for (int j = 1; j < 3; j++) {
                a = min(a, dp[j]);
            }
            if (nums[i] < k) {
                a += k - nums[i];
            }
            dp[0] = dp[1];
            dp[1] = dp[2];
            dp[2] = a;
        }
        ll res = dp[0];
        for (int j = 1; j < 3; j++) {
            res = min(res, dp[j]);
        }
        return res;
    }
};

int main() {
    string problemName = "2919";
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
        getline(file_in, line_in);
        auto k = jread_int(line_in);
        auto res = sol.minIncrementOperations(nums, k);
        getline(file_out, line_out);
        auto ans = jread_longlong(line_out);
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