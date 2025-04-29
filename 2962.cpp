#include <vector>
using namespace std;

class Solution
{
public:
    long long countSubarrays(vector<int> &nums, int k)
    {
        int n = nums.size();
        int max = 0;
        for (int i = 0; i < n; i++)
        {
            if (nums[i] > max)
            {
                max = nums[i];
            }
        }
        int j = 0;
        int c = 0;
        long long ans = 0;
        for (int i = 0; i < n; i++)
        {
            if (nums[i] == max)
            {
                c++;
            }
            while (c >= k)
            {
                if (nums[j] == max)
                {
                    c--;
                }
                j++;
            }
            ans += j;
        }
        return ans;
    }
};

vector<int> nums = {1, 3, 2, 3, 3}; // 6
int k = 2;

int main()
{
    Solution sol;
    long long ans = sol.countSubarrays(nums, k);
    printf("ans = %lld\n", ans);
    return 0;
}