#include <vector>
using namespace std;

class Solution {
   public:
    vector<int> buildArray(vector<int>& nums) {
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            nums[i] += ((nums[nums[i]] & 0b1111111111) << 10);
        }
        for (int i = 0; i < n; i++) {
            nums[i] = nums[i] >> 10;
        }
        return nums;
    }
};

// [0,1,2,4,5,3]
vector<int> nums = {0, 2, 1, 5, 3, 4};

int main() {
    Solution sol;
    vector<int> ans = sol.buildArray(nums);
    printf("ans = [%d", ans[0]);
    for (int i = 1; i < ans.size(); i++) {
        printf(",%d", ans[i]);
    }
    printf("]\n");
    return 0;
}