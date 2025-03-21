#include <vector>
#include <unordered_set>
using namespace std;

class Solution
{
public:
    vector<int> twoSum(vector<int> &nums, int target)
    {
        unordered_map<int, int> set;
        vector<int> ans;
        for (int i = 0; nums.size(); i++)
        {
            auto findit = set.find(target - nums[i]);
            if (findit == set.end())
            {
                set[nums[i]] = i;
            }
            else
            {
                ans = {findit->second, i};
                break;
            }
        }
        return ans;
    }
};

vector<int> nums = {2, 7, 11, 15};
int target = 9;

int main()
{
    Solution sol;
    vector<int> ans = sol.twoSum(nums, target);
    printf("ans = [%d, %d]\n", ans[0], ans[1]); // [0, 1]
    return 0;
}