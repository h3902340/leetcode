#include <vector>
#include <stack>
using namespace std;

class Solution
{
public:
    vector<int> maxPoints(vector<vector<int>> &grid, vector<int> &queries)
    {
        int m = grid.size();
        int n = grid[0].size();
        int k = queries.size();
        vector<pair<int, int>> queriesVec(k);
        for (int i = 0; i < k; i++)
        {
            queriesVec[i] = {i, queries[i]};
        }
        radixSort(queriesVec);
        vector<stack<pair<int, int>>> s(k + 1);
        addToStack(grid, 0, 0, s, queriesVec, k, 0);
        int sum = 0;
        vector<int> ans(k);
        for (int x = 0; x < k; x++)
        {
            while (!s[x].empty())
            {
                pair<int, int> cell = s[x].top();
                s[x].pop();
                if (grid[cell.first][cell.second] == -1)
                    continue;
                sum++;
                if (cell.first > 0)
                {
                    addToStack(grid, cell.first - 1, cell.second, s, queriesVec, k, x);
                }
                if (cell.first < m - 1)
                {
                    addToStack(grid, cell.first + 1, cell.second, s, queriesVec, k, x);
                }
                if (cell.second > 0)
                {
                    addToStack(grid, cell.first, cell.second - 1, s, queriesVec, k, x);
                }
                if (cell.second < n - 1)
                {
                    addToStack(grid, cell.first, cell.second + 1, s, queriesVec, k, x);
                }
                grid[cell.first][cell.second] = -1;
            }
            ans[queriesVec[x].first] = sum;
        }
        return ans;
    }

private:
    void addToStack(vector<vector<int>> &grid, int i, int j, vector<stack<pair<int, int>>> &s, vector<pair<int, int>> &queries, int k, int curr_x)
    {
        if (grid[i][j] <= 0)
            return;
        int left = curr_x;
        int right = k - 1;
        int x = k;
        while (left <= right)
        {
            int mid = (left + right) >> 1;
            if (queries[mid].second > grid[i][j])
            {
                x = mid;
                right = mid - 1;
            }
            else
            {
                left = mid + 1;
            }
        }
        s[x].push({i, j});
        grid[i][j] = 0;
    }
    const int BUCKET_SIZE = 1024;
    const int MASK = 1023;
    void radixSort(vector<pair<int, int>> &nums)
    {
        int n = nums.size();
        vector<int> buckets(BUCKET_SIZE);
        vector<pair<int, int>> temp(n);
        for (int j = 0; j < 20; j += 10)
        {
            for (auto &e : nums)
            {
                buckets[(e.second >> j) & MASK]++;
            }
            for (int i = 1; i < BUCKET_SIZE; i++)
            {
                buckets[i] += buckets[i - 1];
            }
            for (int i = n - 1; i >= 0; i--)
            {
                temp[--buckets[(nums[i].second >> j) & MASK]] = nums[i];
            }
            fill(buckets.begin(), buckets.end(), 0);
            nums.swap(temp);
        }
    }
};

vector<vector<int>> grid = {{1, 2, 3}, {2, 5, 7}, {3, 5, 1}};
vector<int> queries = {5, 6, 2};

int main()
{
    Solution sol;
    vector<int> ans = sol.maxPoints(grid, queries);
    printf("[%d", ans[0]);
    for (int i = 1; i < ans.size(); i++)
    {
        printf(", %d", ans[i]);
    }
    printf("]\n"); // [5,8,1]
    return 0;
}