#include <vector>
using namespace std;

class Solution
{
public:
    int findNumbers(vector<int> &nums)
    {
        int n = nums.size();
        int ans = 0;
        for (int i = 0; i < n; i++)
        {
            int m = 1;
            int d = 0;
            while (m <= nums[i])
            {
                m *= 10;
                d++;
            }
            ans += !(d & 1);
        }
        return ans;
    }
};

vector<int> nums = {12, 345, 2, 6, 7896}; // 2

int main()
{
    Solution sol;
    int ans = sol.findNumbers(nums);
    printf("ans = %d\n", ans);
    return 0;
}