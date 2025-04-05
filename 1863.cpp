#include <vector>
using namespace std;

class Solution
{
public:
    int subsetXORSum(vector<int> &nums)
    {
        int n = nums.size();
        int orResult = 0;
        for (int j = 0; j < n; j++)
        {
            orResult |= nums[j];
        }
        return orResult * fastPow(2, n - 1);
    }

private:
    int fastPow(int a, int b)
    {
        if (b == 0)
            return 1;
        if (b & 1)
        {
            long temp = fastPow(a, b - 1);
            return a * temp;
        }
        long temp = fastPow(a, b >> 1);
        return temp * temp;
    }
};

vector<int> nums = {5, 1, 6};
// 101, 001, 110      4,4,4 ---> 4 + 4 * 2 + 4 * 4 = 28
int main()
{
    Solution sol;
    int ans = sol.subsetXORSum(nums);
    printf("ans = %d\n", ans); // 480;
    return 0;
}