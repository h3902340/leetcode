#include <vector>
using namespace std;

class Solution
{
public:
    int countSubarrays(vector<int> &nums)
    {
        int n = nums.size();
        int ans = 0;
        for (int i = 0; i < n - 2; i++)
        {
            if ((nums[i] + nums[i + 2]) << 1 == nums[i + 1])
            {
                ans++;
            }
        }
        return ans;
    }
};

vector<int> nums = {1, 2, 1, 4, 1}; // 1

int main()
{
    Solution sol;
    int ans = sol.countSubarrays(nums);
    printf("ans = %d\n", ans);
    return 0;
}