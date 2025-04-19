#include <vector>
using namespace std;

class Solution
{
public:
    long long countFairPairs(vector<int> &nums, int lower, int upper)
    {
        int n = nums.size();
        radixSort(nums, n);
        return countNoGreater(nums, n, upper) - countNoGreater(nums, n, lower - 1);
    }

private:
    long long countNoGreater(vector<int> &nums, int n, int cap)
    {
        int l = 0;
        int r = n - 1;
        long long ans = 0;
        while (l < r)
        {
            if (nums[l] + nums[r] > cap)
            {
                r--;
            }
            else
            {
                ans += r - l;
                l++;
            }
        }
        return ans;
    }
    const int BUCKET_SIZE = 256;
    const int MASK = 255;
    const int BIAS = 0x80000000;
    void radixSort(vector<int> &nums, int n)
    {
        for (int i = 0; i < n; i++)
        {
            nums[i] ^= BIAS;
        }
        vector<int> buckets(BUCKET_SIZE);
        vector<int> temp(n);
        for (int j = 0; j < 32; j += 8)
        {
            for (auto &e : nums)
            {
                buckets[(e >> j) & MASK]++;
            }
            for (int i = 1; i < BUCKET_SIZE; i++)
            {
                buckets[i] += buckets[i - 1];
            }
            for (int i = n - 1; i >= 0; i--)
            {
                temp[--buckets[(nums[i] >> j) & MASK]] = nums[i];
            }
            fill(buckets.begin(), buckets.end(), 0);
            nums.swap(temp);
        }
        for (int i = 0; i < n; i++)
        {
            nums[i] ^= BIAS;
        }
    }
};

// vector<int> nums = {0, 1, 7, 4, 4, 5}; // ans = 6
// int lower = 3;
// int upper = 6;
// vector<int> nums = {1, 7, 9, 2, 5}; // ans = 1
// int lower = 11;
// int upper = 11;

vector<int> nums = {-2, -6, 4, 0, -1000000000, -1000000000, -1000000000, -1000000000}; // ans = 6
int lower = -15;
int upper = 15;

int main()
{
    Solution sol;
    long long ans = sol.countFairPairs(nums, lower, upper);
    printf("ans = %lld\n", ans);
    return 0;
}