#include <vector>
using namespace std;

class Solution
{
public:
    int minZeroArray(vector<int> &nums, vector<vector<int>> &queries)
    {
        int n = nums.size();
        int q = queries.size();
        vector<int> delta(n + 1, 0);
        int cap = 0;
        int k = 0;
        for (int i = 0; i < n; i++)
        {
            cap += delta[i];
            while (nums[i] > cap && k < q)
            {
                int start = queries[k][0];
                if (i < start)
                {
                    delta[start] += queries[k][2];
                }
                else
                {
                    cap += queries[k][2];
                }

                int end = queries[k][1] + 1;
                if (i < end)
                {
                    delta[end] -= queries[k][2];
                }
                else
                {
                    cap -= queries[k][2];
                }
                k++;
            }
            if (nums[i] > cap)
            {
                k = -1;
                break;
            }
        }
        return k;
    }
};

vector<int> nums = {6, 7};
vector<vector<int>> queries = {{1, 1, 2}, {1, 1, 5}, {1, 1, 1}, {0, 1, 4}, {0, 1, 3}, {0, 1, 2}, {1, 1, 1}, {1, 1, 2}, {0, 1, 1}, {0, 1, 3}, {1, 1, 5}, {1, 1, 5}, {0, 1, 3}, {1, 1, 5}, {1, 1, 5}};

int main()
{
    Solution sol;
    int k = sol.minZeroArray(nums, queries);
    printf("k = %d\n", k);
    return 0;
}