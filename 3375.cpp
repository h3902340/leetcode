#include <vector>
#include <bitset>
using namespace std;

class Solution
{
public:
    int minOperations(vector<int> &nums, int k)
    {
        int n = nums.size();
        const u_long one = 1;
        u_long bits[2]{0};
        for (int i = 0; i < n; i++)
        {
            if (nums[i] < 64)
            {
                bits[0] |= one << nums[i];
            }
            else
            {
                bits[1] |= one << (nums[i] - 64);
            }
        }
        int ans = 0;
        if (k >= 64)
        {
            if (bits[0])
                return -1;
            k -= 64;
            if (k > 0 && bits[1] & ((one << k) - 1))
                return -1;
            bits[1] >>= (k + 1);
            while (bits[1])
            {
                ans += bits[1] & 1;
                bits[1] >>= 1;
            }
        }
        else
        {
            if (bits[0] & ((one << k) - 1))
                return -1;
            bits[0] >>= k;
            bits[0] >>= 1;
            while (bits[0])
            {
                ans += bits[0] & 1;
                bits[0] >>= 1;
            }
            while (bits[1])
            {
                ans += bits[1] & 1;
                bits[1] >>= 1;
            }
        }

        return ans;
    }
};

vector<int> nums = {56, 42, 63};
int k = 18;

int main()
{
    Solution sol;
    int ans = sol.minOperations(nums, k);
    printf("ans = %d\n", ans);
    return 0;
}