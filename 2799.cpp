#include <vector>
#include <unordered_set>
using namespace std;

class Solution
{
public:
    int countCompleteSubarrays(vector<int> &nums)
    {
        int n = nums.size();
        int map[2001]{0};
        int maxIndex = -1;
        for (int i = 0; i < n; i++)
        {
            if (!map[nums[i]])
            {
                maxIndex = i;
            }
            map[nums[i]]++;
        }
        for (int i = n - 1; i >= maxIndex; i--)
        {
            map[nums[i]]--;
        }
        int ans = 0;
        int j = 0;
        for (int i = maxIndex; i < n; i++)
        {
            map[nums[i]]++;
            while (map[nums[j]] > 1)
            {
                map[nums[j]]--;
                j++;
            }
            ans += (j + 1);
        }
        return ans;
    }
};

vector<int> nums = {1, 3, 1, 2, 2}; // 4

int main()
{
    Solution sol;
    int ans = sol.countCompleteSubarrays(nums);
    printf("ans = %d\n", ans);
    return 0;
}