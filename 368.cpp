#include <vector>
using namespace std;

struct Node
{
    int length;
    int next;
    Node() : length(0), next(-1) {}
};
class Solution
{
public:
    vector<int> largestDivisibleSubset(vector<int> &nums)
    {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        vector<Node> nodes(n);
        int maxOverall = 0;
        int maxOverallIndex = -1;
        for (int i = n - 1; i >= 0; i--)
        {
            int max = 0;
            int maxIndex = -1;
            for (int j = i + 1; j < n; j++)
            {
                if (nums[j] % nums[i] == 0)
                {
                    if (nodes[j].length > max)
                    {
                        max = nodes[j].length;
                        maxIndex = j;
                    }
                }
            }
            nodes[i].length = 1 + max;
            nodes[i].next = maxIndex;
            if (nodes[i].length > maxOverall)
            {
                maxOverall = nodes[i].length;
                maxOverallIndex = i;
            }
        }
        vector<int> ans;
        while (maxOverallIndex != -1)
        {
            ans.push_back(nums[maxOverallIndex]);
            maxOverallIndex = nodes[maxOverallIndex].next;
        }
        return ans;
    }
};

vector<int> nums = {1, 2, 3};

int main()
{
    Solution sol;
    vector<int> ans = sol.largestDivisibleSubset(nums);
    printf("ans = [%d", ans[0]);
    for (int i = 1; i < ans.size(); i++)
    {
        printf(",%d", ans[i]);
    }
    printf("]\n");
    return 0;
}