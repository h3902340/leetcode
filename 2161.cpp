#include <vector>
using namespace std;

class Solution
{
public:
    vector<int> pivotArray(vector<int> &nums, int pivot)
    {
        int n = nums.size();
        vector<int> radices(3);
        for (int i = 0; i < n; i++)
        {
            int radixIndex = (nums[i] < pivot) + ((nums[i] == pivot) << 1);
            radices[radixIndex]++;
        }
        radices[2] += radices[1];
        radices[0] = 0;
        vector<int> ans(n);
        for (int i = 0; i < n; i++)
        {
            int radixIndex = (nums[i] == pivot) + ((nums[i] > pivot) << 1);
            ans[radices[radixIndex]] = nums[i];
            radices[radixIndex]++;
        }
        return ans;
    }
};

vector<int> nums = {18, -13, -19, -11, 5, -17, 0, -18, -12, -6, -20, -8, -20, -4, 8};
int pivot = -20;

int main()
{
    Solution sol;
    vector<int> ans = sol.pivotArray(nums, pivot);
    printf("ans = [");
    for (int i = 0; i < ans.size() - 1; i++)
    {
        printf("%d,", ans[i]);
    }
    printf("%d]\n", ans[ans.size() - 1]); // [-20,-20,18,-13,-19,-11,5,-17,0,-18,-12,-6,-8,-4,8] expected
    return 0;
}