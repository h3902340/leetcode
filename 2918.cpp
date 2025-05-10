#include <iostream>
#include <vector>
using namespace std;

static const char _ = []() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    return 0;
}();

class Solution {
   public:
    long long minSum(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size();
        int n = nums2.size();
        int nums1Zero = 0;
        int nums2Zero = 0;
        long long nums1Sum = 0;
        long long nums2Sum = 0;
        for (int i = 0; i < m; i++) {
            if (nums1[i] == 0) {
                nums1Zero++;
            } else {
                nums1Sum += nums1[i];
            }
        }
        for (int i = 0; i < n; i++) {
            if (nums2[i] == 0) {
                nums2Zero++;
            } else {
                nums2Sum += nums2[i];
            }
        }
        nums1Sum += nums1Zero;
        nums2Sum += nums2Zero;
        if (nums1Sum == nums2Sum) return nums1Sum;
        if (nums1Sum > nums2Sum) {
            if (nums2Zero) {
                return nums1Sum;
            }
            return -1;
        }
        if (nums1Zero) {
            return nums2Sum;
        }
        return -1;
    }
};

// 12
vector<int> nums1 = {3, 2, 0, 1, 0};
vector<int> nums2 = {6, 5, 0};

int main() {
    Solution sol;
    long long ans = sol.minSum(nums1, nums2);
    printf("ans = %lld\n", ans);
    return 0;
}