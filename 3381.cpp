#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define ll long long
const int K = 2e5;
ll prefix[K];
class Solution {
   public:
    long long maxSubarraySum(vector<int>& nums, int k) {
        int n = nums.size();
        ll a = 0;
        for (int i = 0; i < k; i++) {
            a += nums[i];
        }
        ll res = a;
        prefix[0] = a;
        int cap = min(k, n - k + 1);
        for (int i = 1; i < cap; i++) {
            a = a - nums[i - 1] + nums[i - 1 + k];
            prefix[i] = a;
            res = max(res, a);
        }
        int j = 0;
        cap = n + 1 - k;
        for (int i = k; i < cap; i++) {
            a = a - nums[i - 1] + nums[i - 1 + k];
            prefix[j] = max(prefix[j] + a, a);
            res = max(res, prefix[j]);
            j++;
            if (j == k) {
                j -= k;
            }
        }
        return res;
    }
};

int main() {
    string problemName = "3381";
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
        auto res = sol.maxSubarraySum(nums, k);
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