#include <vector>
using namespace std;

class Solution {
   public:
    int minOperations(vector<int> &nums, int k) {
        int n = nums.size();
        int sum = 0;
        for (int i = 0; i < n; i++) {
            sum += nums[i];
        }
        return sum % k;
    }
};

vector<int> nums = {3, 9, 7};
int k = 5;

int main() {
    Solution sol;
    int ans = sol.minOperations(nums, k);
    printf("ans = %d\n", ans);  // 4
    return 0;
}