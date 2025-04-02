#include <vector>
using namespace std;

class Solution
{
public:
    long long maximumTripletValue(vector<int> &nums)
    {
        int n = nums.size();
        int peak = 0;
        int maxSlope = 0;
        long long max = 0;
        for (int i = 0; i < n - 2; i++)
        {
            int j = i + 1;
            if (nums[i] < nums[j])
                continue;
            if (nums[i] > peak)
            {
                peak = nums[i];
            }
            for (; j < n - 1; j++)
            {
                int curSlope = peak - nums[j];
                if (curSlope > maxSlope)
                {
                    maxSlope = curSlope;
                }
                long long cur = (long)maxSlope * nums[j + 1];
                if (cur > max)
                {
                    max = cur;
                }
                if (nums[j] < nums[j + 1])
                    break;
            }
            j++;
            for (; j < n; j++)
            {
                long long cur = (long)maxSlope * nums[j];
                if (cur > max)
                {
                    max = cur;
                }
                if (j + 1 < n && nums[j] > nums[j + 1])
                    break;
            }
            i = j - 1;
        }
        return max;
    }
};

vector<int> nums = {6, 11, 12, 12, 7, 9, 2, 11, 12, 4, 19, 14, 16, 8, 16};

int main()
{
    Solution sol;
    long long ans = sol.maximumTripletValue(nums);
    printf("ans = %lld\n", ans); // 190
    return 0;
}