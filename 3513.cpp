#include <vector>
using namespace std;

class Solution {
   public:
    int uniqueXorTriplets(vector<int> &nums) {
        int n = nums.size();
        if (n == 1) {
            return 1;
        }
        if (n == 2) {
            return 2;
        }
        return 1 << (32 - __builtin_clz(n));
    }
};

vector<int> nums = {3, 1, 2};

int main() {
    Solution sol;
    int ans = sol.uniqueXorTriplets(nums);
    printf("ans = %d\n", ans);  // 4
    return 0;
}