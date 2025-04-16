#include <vector>
#include <unordered_set>
using namespace std;

class Solution
{
public:
    long long countGood(vector<int> &nums, int k)
    {
        int n = nums.size();
        unordered_map<int, int> map;
        int j = 0;
        long long ans = 0;
        for (int i = 0; i < n; i++)
        {
            k -= map[nums[i]]++;
            while (k <= 0)
            {
                k += --map[nums[j++]];
            }
            ans += j;
        }
        return ans;
    }
};

vector<int> nums = {2, 1, 3, 1, 2, 2, 3, 3, 2, 2, 1, 1, 1, 3, 1};
int k = 11;

int main()
{
    Solution sol;
    long long ans = sol.countGood(nums, k);
    printf("ans = %lld\n", ans); // 21
    return 0;
}