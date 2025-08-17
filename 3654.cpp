#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define ll long long
const int N = 1e5;
const int K = 1e5;
ll dp[N];
int idx[K];

class Solution {
   public:
    long long minArraySum(vector<int>& nums, int k) {
        int n = nums.size();
        for (int i = 0; i < k; i++) {
            idx[i] = -1;
        }
        int s = nums[n - 1] % k;
        if (s == 0) {
            dp[n - 1] = 0;
        } else {
            dp[n - 1] = nums[n - 1];
        }
        idx[s] = n - 1;
        for (int i = n - 2; i >= 0; i--) {
            s = (s + nums[i]) % k;
            if (s == 0) {
                dp[i] = 0;
                continue;
            }
            dp[i] = nums[i] + dp[i + 1];
            int j = idx[s];
            if (j != -1) {
                dp[i] = min(dp[i], dp[j]);
            }
            idx[s] = i;
        }
        return dp[0];
    }
};

int main() {
    string problemName = "3654";
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
        auto res = sol.minArraySum(nums, k);
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