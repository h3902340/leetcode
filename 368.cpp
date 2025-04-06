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

private:
    const int BUCKET_SIZE = 256;
    const int MASK = 255;
    void radixSort(vector<int> &nums)
    {
        int n = nums.size();
        vector<int> buckets(BUCKET_SIZE);
        vector<int> temp(n);
        for (int j = 0; j < 32; j += 8)
        {
            for (auto &e : nums)
            {
                buckets[(e >> j) & MASK]++;
            }
            for (int i = 1; i < BUCKET_SIZE; i++)
            {
                buckets[i] += buckets[i - 1];
            }
            for (int i = n - 1; i >= 0; i--)
            {
                temp[--buckets[(nums[i] >> j) & MASK]] = nums[i];
            }
            fill(buckets.begin(), buckets.end(), 0);
            nums.swap(temp);
        }
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