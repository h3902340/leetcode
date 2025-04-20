#include <vector>
#include <stack>
using namespace std;

class Solution
{
public:
    int maximumPossibleSize(vector<int> &nums)
    {
        int n = nums.size();
        stack<int> s;
        s.push(nums[n - 1]);
        int ans = n;
        for (int i = n - 2; i >= 0; i--)
        {
            int e = s.top();
            while (e < nums[i])
            {
                s.pop();
                ans--;
                if (s.empty())
                {
                    break;
                }
                e = s.top();
            }
            s.push(nums[i]);
        }
        return ans;
    }
};

vector<int> nums = {19, 28, 13, 7, 18, 10, 44, 38, 22, 14};

int main()
{
    Solution sol;
    int ans = sol.maximumPossibleSize(nums);
    printf("ans = %d\n", ans); // 3
    return 0;
}