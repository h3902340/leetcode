#include <vector>
using namespace std;

class Solution
{
public:
    int minimumOperations(vector<int> &nums)
    {
        int n = nums.size();
        int map[101]{0};
        for (int i = n - 1; i >= 0; i--)
        {
            if (map[nums[i]])
            {
                return (i / 3) + 1;
            }
            map[nums[i]] = 1;
        }
        return 0;
    }
};

int main()
{
    vector<int> nums = {1, 2, 3, 4, 2, 3, 3, 5, 7};
    Solution sol;
    int ans = sol.minimumOperations(nums);
    printf("ans = %d\n", ans); // 2
    return 0;
}