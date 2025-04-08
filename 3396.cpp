#include <vector>
#include <unordered_set>
using namespace std;

class Solution
{
public:
    int minimumOperations(vector<int> &nums)
    {
        int n = nums.size();
        unordered_set<int> set;
        int j = 0;
        for (int i = n - 1; i >= 0; i--)
        {
            auto it = set.find(nums[i]);
            if (it != set.end())
            {
                return (i / 3) + 1;
            }
            set.insert(nums[i]);
        }
        return 0;
    }
};

int main()
{
    vector<int> nums = {1, 2, 3, 4, 2, 3, 3, 5, 7};
    Solution sol;
    int ans = sol.minimumOperations(nums);
    printf("ans = %d\n", ans);
    return 0;
}