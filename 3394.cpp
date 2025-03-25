#include <vector>
using namespace std;

class Solution
{
public:
    bool checkValidCuts(int n, vector<vector<int>> &rectangles)
    {
        int r = rectangles.size();
        vector<pair<int, int>> horizontal(r);
        vector<pair<int, int>> vertical(r);
        for (int i = 0; i < r; i++)
        {
            horizontal[i].first = rectangles[i][0];
            horizontal[i].second = rectangles[i][2] - 1;
            vertical[i].first = rectangles[i][1];
            vertical[i].second = rectangles[i][3] - 1;
        }
        radixSort(horizontal);
        int end = horizontal[0].second;
        int division = 0;
        for (int i = 1; i < r; i++)
        {
            if (horizontal[i].first > end)
            {
                division++;
                end = horizontal[i].second;
            }
            else
            {
                if (horizontal[i].second > end)
                {
                    end = horizontal[i].second;
                }
            }
        }
        if (division > 1)
            return true;
        radixSort(vertical);
        end = vertical[0].second;
        division = 0;
        for (int i = 1; i < r; i++)
        {
            if (vertical[i].first > end)
            {
                division++;
                end = vertical[i].second;
            }
            else
            {
                if (vertical[i].second > end)
                {
                    end = vertical[i].second;
                }
            }
        }
        return division > 1;
    }

private:
    const int BUCKET_SIZE = 256;
    const int MASK = 255;
    void radixSort(vector<pair<int, int>> &nums)
    {
        int n = nums.size();
        vector<int> buckets(BUCKET_SIZE);
        vector<pair<int, int>> temp(n);
        for (int j = 0; j < 32; j += 8)
        {
            for (auto &e : nums)
            {
                buckets[(e.first >> j) & MASK]++;
            }
            for (int i = 1; i < BUCKET_SIZE; i++)
            {
                buckets[i] += buckets[i - 1];
            }
            for (int i = n - 1; i >= 0; i--)
            {
                temp[--buckets[(nums[i].first >> j) & MASK]] = nums[i];
            }
            fill(buckets.begin(), buckets.end(), 0);
            nums.swap(temp);
        }
    }
};

int n = 5;
vector<vector<int>> rectangles = {{0, 0, 1, 5}, {1, 0, 3, 3}, {3, 0, 5, 3}, {1, 3, 2, 5}, {2, 3, 5, 5}};

int main()
{
    Solution sol;
    bool ans = sol.checkValidCuts(n, rectangles);
    printf("ans = %s\n", ans ? "true" : "false"); // false
    return 0;
}