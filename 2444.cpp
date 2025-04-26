#include <vector>
using namespace std;
class Solution
{
public:
    long long countSubarrays(vector<int> &nums, int minK, int maxK)
    {
        int n = nums.size();
        int j = 0;
        int left = 0;
        int lastMin = -1;
        int lastMax = -1;
        long long ans = 0;
        for (int i = 0; i < n; i++)
        {
            if (nums[i] < minK || nums[i] > maxK)
            {
                j = i + 1;
                lastMin = -1;
                lastMax = -1;
                left = 0;
                continue;
            }
            if (nums[i] == minK)
            {
                lastMin = i;
            }
            if (nums[i] == maxK)
            {
                lastMax = i;
            }
            if (lastMin != -1 && lastMax != -1)
            {
                if (lastMin < lastMax)
                {
                    int newj = lastMin + 1;
                    lastMin = -1;
                    left += newj - j;
                    j = newj;
                }
                else if (lastMin == lastMax)
                {
                    int newj = lastMin + 1;
                    lastMin = -1;
                    lastMax = -1;
                    left += newj - j;
                    j = newj;
                }
                else
                {
                    int newj = lastMax + 1;
                    lastMax = -1;
                    left += newj - j;
                    j = newj;
                }
            }
            ans += left;
        }
        return ans;
    }
};

/* vector<int> nums = {1, 3, 5, 2, 7, 5}; // 2
int minK = 1;
int maxK = 5; */

/* vector<int> nums = {1, 1, 1, 1}; // 10
int minK = 1;
int maxK = 1;
 */

vector<int> nums = {8121, 8121, 955792, 925378, 383928, 673920, 457030, 925378, 925378, 925378, 92893, 456370, 925378}; // 0
int minK = 8121;
int maxK = 925378;

int main()
{
    Solution sol;
    long long ans = sol.countSubarrays(nums, minK, maxK);
    printf("ans = %lld\n", ans);
    return 0;
}