#include <vector>
using namespace std;

class Solution
{
public:
    bool divideArray(vector<int> &nums)
    {
        int n = nums.size();
        bool arr[501] = {0};

        for (int i = 0; i < n; i++)
        {
            arr[nums[i]] = !arr[nums[i]];
        }
        bool result = true;
        for (int i = 0; i < 501; i++)
        {
            result &= !arr[i];
        }
        return result;
    }
};

vector<int> nums = {3, 2, 3, 2, 2, 2};

int main()
{
    Solution sol;
    bool ans = sol.divideArray(nums);
    printf("ans = %d\n", ans == true); // 1
    return 0;
}