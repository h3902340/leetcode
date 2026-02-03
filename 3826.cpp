#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define ll long long
const int N = 1000;
ll dp[N];
int seg[N];
class Solution {
   public:
    long long minPartitionScore(vector<int>& nums, int k) {
        int n = nums.size();
        for (int i = 1; i < n; i++) {
            nums[i] += nums[i - 1];
        }
        ll l = 0;
        ll r = (ll)nums[n - 1] * nums[n - 1];
        while (l <= r) {
            ll mid = (l + r) >> 1;
            dp[0] = (ll)nums[0] * nums[0] + mid;
            seg[0] = 1;
            for (int i = 1; i < n; i++) {
                ll a = nums[i];
                dp[i] = a * a + mid;
                seg[i] = 1;
                for (int j = 0; j < i; j++) {
                    a = nums[i] - nums[j];
                    ll b = a * a + dp[j] + mid;
                    if (dp[i] > b) {
                        seg[i] = 1 + seg[j];
                        dp[i] = b;
                    }
                }
            }
            if (seg[n - 1] == k) {
                return (dp[n - 1] - k * mid + nums[n - 1]) >> 1;
            }
            if (seg[n - 1] < k) {
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        return 0;
    }
};

int main() {
    string problemName = "3826";
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
        auto res = sol.minPartitionScore(nums, k);
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