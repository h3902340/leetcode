#include <vector>
using namespace std;

class Solution
{
public:
    long long countSubarrays(vector<int> &nums, long long k)
    {
        int n = nums.size();
        long long sum = 0;
        int count = 0;
        long long ans = 0;
        int j = 0;
        for (int i = 0; i < n; i++)
        {
            sum += nums[i];
            count++;
            while (sum * count >= k)
            {
                sum -= nums[j];
                j++;
                count--;
            }
            ans += count;
        }
        return ans;
    }
};

vector<int> nums = {2, 1, 4, 3, 5}; // 6
long long k = 10;

int main()
{
    Solution sol;
    long long ans = sol.countSubarrays(nums, k);
    printf("ans = %lld\n", ans);
    return 0;
}