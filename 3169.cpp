#include <vector>
#include <unordered_map>
using namespace std;

class Solution
{
private:
    void radixSort(vector<vector<int>> &nums)
    {
        int n = nums.size();
        int buckets[256]{0};
        vector<vector<int>> ans(n);
        // 7-0 bit
        for (int i = 0; i < n; i++)
        {
            buckets[nums[i][0] & 255]++;
        }
        for (int i = 0; i < 255; i++)
        {
            buckets[i + 1] += buckets[i];
        }
        for (int i = n - 1; i >= 0; i--)
        {
            ans[--buckets[nums[i][0] & 255]] = nums[i];
        }
        fill_n(buckets, 256, 0);
        // 15-8 bit
        for (int i = 0; i < n; i++)
        {
            buckets[(ans[i][0] >> 8) & 255]++;
        }
        for (int i = 0; i < 255; i++)
        {
            buckets[i + 1] += buckets[i];
        }
        for (int i = n - 1; i >= 0; i--)
        {
            nums[--buckets[(ans[i][0] >> 8) & 255]] = ans[i];
        }
        // 23-16 bit
        fill_n(buckets, 256, 0);
        for (int i = 0; i < n; i++)
        {
            buckets[(nums[i][0] >> 16) & 255]++;
        }
        for (int i = 0; i < 255; i++)
        {
            buckets[i + 1] += buckets[i];
        }
        for (int i = n - 1; i >= 0; i--)
        {
            ans[--buckets[(nums[i][0] >> 16) & 255]] = nums[i];
        }
        // 31-24 bit
        fill_n(buckets, 256, 0);
        for (int i = 0; i < n; i++)
        {
            buckets[(ans[i][0] >> 24) & 255]++;
        }
        for (int i = 0; i < 255; i++)
        {
            buckets[i + 1] += buckets[i];
        }
        for (int i = n - 1; i >= 0; i--)
        {
            nums[--buckets[(ans[i][0] >> 24) & 255]] = ans[i];
        }
    }

public:
    int countDays(int days, vector<vector<int>> &meetings)
    {
        int n = meetings.size();
        radixSort(meetings);
        int ans = meetings[0][0] - 1;
        int end = meetings[0][1] + 1;
        for (int i = 1; i < n; i++)
        {
            if (meetings[i][0] > end)
            {
                ans += (meetings[i][0] - end);
                end = meetings[i][1] + 1;
            }
            else
            {
                int newEnd = meetings[i][1] + 1;
                if (newEnd > end)
                {
                    end = newEnd;
                }
            }
        }
        if (end <= days)
        {
            ans += (days - end + 1);
        }
        return ans;
    }
};

int days = 10;
vector<vector<int>> meetings = {{5, 7}, {1, 3}, {9, 10}};

int main()
{
    Solution sol;
    int ans = sol.countDays(days, meetings);
    printf("ans = %d\n", ans); // 2
    return 0;
}