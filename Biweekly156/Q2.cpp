#include <queue>
#include <vector>
using namespace std;

const int NMAX = 1e5;
int s[NMAX];

class Solution {
   public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();
        int top = 0;
        int i = 0;
        while (i < n && nums[i] == 0) {
            i++;
        }
        if (i == n) return 0;
        int ans = 1;
        s[top] = nums[i++];
        for (; i < n; i++) {
            while (top >= 0 && nums[i] < s[top]) {
                top--;
            }
            if (top == -1) {
                if (nums[i] != 0) {
                    s[++top] = nums[i];
                    ans++;
                }
            } else if (nums[i] != s[top]) {
                s[++top] = nums[i];
                ans++;
            }
        }
        return ans;
    }
};

// 4
/* vector<int> nums = {4, 3, 4, 6}; */

// 1
/* vector<int> nums = {4, 4}; */

int main() {
    Solution sol;
    vector<int> nums;
    for (int i = 0; i < 40000; i++) {
        nums.push_back(i);
    }
    int ans = sol.minOperations(nums);
    printf("ans = %d\n", ans);
    return 0;
}