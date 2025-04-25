#include <vector>
#include <unordered_map>
using namespace std;

const int NMAX = 1e+5;
int prefix[NMAX + 1];
class Solution
{
public:
    long long countInterestingSubarrays(vector<int> &nums, int modulo, int k)
    {
        int n = nums.size();
        int j = 0;
        int pre = -1;
        long long ans = 0;
        long long gap_total = 0;
        for (int i = 0; i < n; i++)
        {
            if (nums[i] % modulo == k)
            {
                int diff = i - pre;
                pre = i;
                int r = (j - k + modulo) % modulo;
                if (r < j)
                {
                    ans += diff * prefix[r];
                }
                if (j < modulo)
                {
                    prefix[j] = diff;
                }
                else
                {
                    prefix[j % modulo] += diff;
                }
                gap_total += (long long)diff * (diff - 1) >> 1;
                j++;
            }
        }
        int diff = n - pre;
        int r = (j - k + modulo) % modulo;
        if (r < j)
        {
            ans += diff * prefix[r];
        }
        gap_total += (long long)diff * (diff - 1) >> 1;
        if (k == 0)
        {
            ans += gap_total;
        }
        return ans;
    }
};

/* vector<int> nums = {3, 2, 4}; // 3
int modulo = 2;
int k = 1; */

vector<int> nums = {3, 1, 9, 6}; // 2
int modulo = 3;
int k = 0;

/* vector<int> nums = {7, 2}; // 1
int modulo = 7;
int k = 0; */

int main()
{
    Solution sol;
    long long ans = sol.countInterestingSubarrays(nums, modulo, k);
    printf("ans = %lld\n", ans);
    return 0;
}