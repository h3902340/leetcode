#include <vector>
using namespace std;

class Solution
{
public:
    int findDuplicate(vector<int> &nums)
    {
        // Using Floyd's tortoise and hare algorithm
        int tortoise = nums[0];
        int hare = nums[0];
        for (int i = 0; i < nums.size(); i++)
        {
            tortoise = nums[tortoise];
            hare = nums[hare];
            hare = nums[hare];
            if (tortoise == hare)
                break;
        }
        int human = nums[0];
        int humanPre = human;
        int tortoisePre = tortoise;
        for (int i = 0; i < nums.size(); i++)
        {
            if (human == tortoise)
                break;
            humanPre = human;
            tortoisePre = tortoise;
            human = nums[human];
            tortoise = nums[tortoise];
        }
        if (humanPre == tortoisePre)
        {
            return humanPre;
        }
        else
        {
            return human;
        }
    }
};

vector<int> nums = {3, 1, 3, 4, 2};

int main()
{
    Solution sol;
    int ans = sol.findDuplicate(nums);
    printf("ans = %d", ans);
    return 0;
}