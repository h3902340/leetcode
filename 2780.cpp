#include <vector>
using namespace std;

class Solution
{
public:
    int minimumIndex(vector<int> &nums)
    {
        int n = nums.size();
        int counter = 0;
        int dominant = 0;
        for (int i = 0; i < n; i++)
        {
            if (counter == 0)
            {
                dominant = nums[i];
                counter++;
            }
            else
            {
                if (nums[i] == dominant)
                {
                    counter++;
                }
                else
                {
                    counter--;
                }
            }
        }
        int i = 0;
        counter = 0;
        for (; i < n; i++)
        {
            if (nums[i] == dominant)
            {
                counter++;
                if (counter << 1 > i + 1)
                {
                    break;
                }
            }
        }
        if (n & 1)
        {
            for (int j = i + 1; j < n; j++)
            {
                if (nums[j] == dominant)
                {
                    counter++;
                }
            }
            if (counter << 1 == n + 1)
            {
                return -1;
            }
        }
        return i;
    }
};

vector<int> nums = {1, 2, 2, 2};

int main()
{
    Solution sol;
    int ans = sol.minimumIndex(nums);
    printf("ans = %d\n", ans); // 2
    return 0;
}