#include <vector>
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
        vector<vector<pair<int, int>>> s(k + 1);
        addToQueue(grid, 0, 0, s, queriesVec, k, 0);
        int sum = 0;
        for (int x = 0; x < k; x++)
        {
            int l = 0;
            while (l < s[x].size())
            {
                pair<int, int> cell = s[x][l++];
                if (grid[cell.first][cell.second] == -1)
                    continue;
                sum++;
                if (cell.first > 0)
                {
                    addToQueue(grid, cell.first - 1, cell.second, s, queriesVec, k, x);
                }
                if (cell.first + 1 < m)
                {
                    addToQueue(grid, cell.first + 1, cell.second, s, queriesVec, k, x);
                }
                if (cell.second > 0)
                {
                    addToQueue(grid, cell.first, cell.second - 1, s, queriesVec, k, x);
                }
                if (cell.second + 1 < n)
                {
                    addToQueue(grid, cell.first, cell.second + 1, s, queriesVec, k, x);
                }
                grid[cell.first][cell.second] = -1;
            }
            queries[queriesVec[x].first] = sum;
        }
        return queries;
    }

private:
    void addToQueue(vector<vector<int>> &grid, int i, int j, vector<vector<pair<int, int>>> &s, vector<pair<int, int>> &queries, int k, int curr_x)
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
        s[x].emplace_back(i, j);
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

vector<vector<int>> grid = {{420766, 806051, 922751}, {181527, 815280, 904568}, {952102, 4037, 140319}, {324081, 17907, 799523}, {176688, 90257, 83661}, {932477, 621193, 623068}, {135839, 554701, 511427}, {227575, 450848, 178065}, {785644, 204668, 835141}, {313774, 167359, 501496}, {641317, 620688, 74989}, {324499, 122376, 270369}, {2121, 887154, 848859}, {456704, 7763, 662087}, {286827, 145349, 468865}, {277137, 858176, 725551}, {106131, 93684, 576512}, {372563, 944355, 497187}, {884187, 600892, 268120}, {576578, 515031, 807686}};
vector<int> queries = {352655, 586228, 169685, 541073, 584647, 413832, 576537, 616413};

int main()
{
    Solution sol;
    vector<int> ans = sol.maxPoints(grid, queries);
    printf("[%d", ans[0]);
    for (int i = 1; i < ans.size(); i++)
    {
        printf(", %d", ans[i]);
    }
    printf("]\n"); // [0,2,0,2,2,0,2,2]
    return 0;
}