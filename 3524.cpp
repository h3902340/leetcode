#include <vector>
using namespace std;

// TODO: time is bad (164 ms)
class Solution {
   public:
    vector<long long> resultArray(vector<int> &nums, int k) {
        int n = nums.size();
        vector<vector<long long>> ans(n, vector<long long>(k, 0));
        ans[0][nums[0] % k] = 1;
        for (int i = 1; i < n; i++) {
            ans[i][nums[i] % k]++;
            for (int j = 0; j < k; j++) {
                ans[i][(long long)j * nums[i] % k] += ans[i - 1][j];
            }
        }
        for (int i = 0; i < k; i++) {
            for (int j = 1; j < n; j++) {
                ans[j][i] += ans[j - 1][i];
            }
        }
        return ans[n - 1];
    };
};

vector<int> nums = {1, 2, 3, 4, 5};
int k = 3;

int main() {
    Solution sol;
    vector<long long> ans = sol.resultArray(nums, k);
    printf("ans = [%lld", ans[0]);
    for (int i = 1; i < ans.size(); i++) {
        printf(",%lld", ans[i]);
    }
    printf("]\n");  // [9,2,4]
    return 0;
}