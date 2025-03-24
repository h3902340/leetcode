#include <vector>
#include <unordered_map>
using namespace std;

struct Meeting
{
    int start;
    int end;
};
class Solution
{
private:
    const int BUCKET_SIZE = 256;
    const int MASK = 255;
    void radixSort(vector<Meeting> &nums)
    {
        int n = nums.size();
        vector<int> buckets(BUCKET_SIZE);
        vector<Meeting> temp(n);
        for (int j = 0; j < 32; j += 8)
        {
            for (auto &e : nums)
            {
                buckets[(e.start >> j) & MASK]++;
            }
            for (int i = 1; i < BUCKET_SIZE; i++)
            {
                buckets[i] += buckets[i - 1];
            }
            for (int i = n - 1; i >= 0; i--)
            {
                temp[--buckets[(nums[i].start >> j) & MASK]] = nums[i];
            }
            fill(buckets.begin(), buckets.end(), 0);
            nums.swap(temp);
        }
    }

public:
    int countDays(int days, vector<vector<int>> &meetings)
    {
        int n = meetings.size();
        vector<Meeting> vec(n);
        for (int i = 0; i < n; i++)
        {
            vec[i] = {meetings[i][0], meetings[i][1]};
        }
        radixSort(vec);
        int ans = days;
        int start = 0;
        int end = -1;
        for (auto &v : vec)
        {
            if (v.start > end)
            {
                ans -= (end - start + 1);
                start = v.start;
                end = v.end;
            }
            else
            {
                if (v.end > end)
                {
                    end = v.end;
                }
            }
        }
        ans -= (end - start + 1);
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