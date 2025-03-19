#include <vector>
using namespace std;

class Solution
{
public:
    int minOperations(vector<int> &nums)
    {
        int n = nums.size();
        int count = 0;
        for (int i = 0; i < n - 2; i++)
        {
            if (!nums[i])
            {
                nums[i] = 1;
                nums[i + 1] = !nums[i + 1];
                nums[i + 2] = !nums[i + 2];
                count++;
            }
        }
        if (nums[n - 2] & nums[n - 1])
        {
            return count;
        }
        return -1;
    }
};

vector<int> nums = {0, 1, 1, 1, 0, 0};

int main()
{
    Solution sol;
    int ans = sol.minOperations(nums);
    printf("ans = %d\n", ans); // 3
    return 0;
}