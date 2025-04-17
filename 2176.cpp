#include <vector>
using namespace std;

// cba to think of an O(nlogn) solution, the testcases are too small
class Solution
{
public:
    int countPairs(vector<int> &nums, int k)
    {
        int n = nums.size();
        int count = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                if (nums[i] == nums[j] && i * j % k == 0)
                {
                    count++;
                }
            }
        }
        return count;
    }
};

vector<int> nums = {3, 1, 2, 2, 2, 1, 3};
int k = 2;

int main()
{
    Solution sol;
    sol.countPairs(nums, k);
    return 0;
}