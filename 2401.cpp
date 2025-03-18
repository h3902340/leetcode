#include <vector>
using namespace std;

class Solution
{
public:
    int longestNiceSubarray(vector<int> &nums)
    {
        int n = nums.size();
        int bits = 0;
        int i = 0;
        int j = 0;
        int max = 0;
        for (j = 0; j < n; j++)
        {
            while (bits & nums[j])
            {
                bits -= nums[i];
                i++;
            }
            bits += nums[j];
            int current = j - i + 1;
            if (current > max)
            {
                max = current;
            }
        }
        return max;
    }
};

vector<int> nums = {1, 3, 8, 48, 10};

int main()
{
    Solution sol;
    int ans = sol.longestNiceSubarray(nums);
    printf("ans = %d\n", ans); // 3
    return 0;
}