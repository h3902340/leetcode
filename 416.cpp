#include <vector>
#include <bitset>
using namespace std;

class Solution
{
public:
    bool canPartition(vector<int> &nums)
    {
        int n = nums.size();
        int sum = 0;
        for (int i = 0; i < n; i++)
        {
            sum += nums[i];
        }
        if (sum & 1)
            return false;
        sum >>= 1;
        bitset<10001> bit(1);
        for (int i = 0; i < n; i++)
        {
            bit |= bit << nums[i];
            if (bit[sum])
                return true;
        }
        return false;
    }
};

vector<int> nums = {1, 5, 11, 5};

int main()
{
    Solution sol;
    bool ans = sol.canPartition(nums);
    printf("ans = %s\n", ans ? "true" : "false"); // true
    return 0;
}