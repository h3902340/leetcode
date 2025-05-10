#include <unordered_map>
#include <vector>
#include <iostream>
using namespace std;

class Solution {
   public:
    long long countInterestingSubarrays(vector<int>& nums, int modulo, int k) {
        int n = nums.size();
        int j = 0;
        int pre = -1;
        int64_t ans = 0;
        int64_t gap_total = 0;
        int diff = 0;
        int r = 0;
        for (int i = 0; i < n; i++) {
            if (nums[i] % modulo == k) {
                diff = i - pre;
                pre = i;
                r = (j - k + modulo) % modulo;
                if (r < j) {
                    ans += diff * nums[r];
                }
                if (j < modulo) {
                    nums[j] = diff;
                } else {
                    nums[j % modulo] += diff;
                }
                gap_total += (int64_t)diff * (diff - 1) >> 1;
                j++;
            }
        }
        diff = n - pre;
        r = (j - k + modulo) % modulo;
        if (r < j) {
            ans += diff * nums[r];
        }
        gap_total += (int64_t)diff * (diff - 1) >> 1;
        if (k == 0) {
            ans += gap_total;
        }
        return ans;
    }
};

static const char _ = []() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    return 0;
}();

/* vector<int> nums = {3, 2, 4}; // 3
int modulo = 2;
int k = 1; */

vector<int> nums = {3, 1, 9, 6};  // 2
int modulo = 3;
int k = 0;

/* vector<int> nums = {7, 2}; // 1
int modulo = 7;
int k = 0; */

int main() {
    Solution sol;
    long long ans = sol.countInterestingSubarrays(nums, modulo, k);
    printf("ans = %lld\n", ans);
    return 0;
}