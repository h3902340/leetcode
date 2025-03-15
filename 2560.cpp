#include <vector>
using namespace std;

class Solution
{
public:
    int minCapability(vector<int> &nums, int k)
    {
        int n = nums.size();
        int minMax = INT_MAX;
        int left = 1;
        int right = nums[0];
        for (int i = 1; i < n; i++)
        {
            if (right < nums[i])
            {
                right = nums[i];
            }
        }
        int mid = -1;
        while (left <= right)
        {
            mid = (left + right) >> 1;
            int kMax = 0;
            int i = 0;
            while (i < n)
            {
                if (nums[i] > mid)
                {
                    i++;
                    continue;
                }
                kMax++;
                i += 2;
            }
            if (kMax < k)
            {
                left = mid + 1;
            }
            else
            {
                minMax = mid;
                right = mid - 1;
            }
        }

        return minMax;
    }
};

vector<int> nums = {2, 3, 5, 9};
int k = 2;

int main()
{
    Solution sol;
    int ans = sol.minCapability(nums, k);
    printf("ans = %d\n", ans); // 5
    return 0;
}