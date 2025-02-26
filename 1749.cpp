#include <vector>
using namespace std;

class Solution
{
public:
    int maxAbsoluteSum(vector<int> &nums)
    {
        int max = INT_MIN;
        int currentMax = 0;
        int currentMin = 0;
        for (int i : nums)
        {
            currentMax += i;
            currentMin += i;
            if (i > currentMax)
            {
                currentMax = i;
            }
            if (i < currentMin)
            {
                currentMin = i;
            }
            if (abs(currentMax) > max)
            {
                max = abs(currentMax);
            }
            if (abs(currentMin) > max)
            {
                max = abs(currentMin);
            }
        }
        return max;
    }
};

vector<int> nums = {2, -5, 1, -4, 3, -2};

int main()
{
    Solution sol;
    int ans = sol.maxAbsoluteSum(nums);
    printf("ans = %d\n", ans);
    return 0;
}