#include <vector>
#include <unordered_map>
using namespace std;

struct Node
{
    int day;
    int delta;
};
class Solution
{
private:
    void radixSort(vector<Node> &nums)
    {
        int n = nums.size();
        int buckets[256]{0};
        vector<Node> ans(n);
        // 7-0 bit
        for (int i = 0; i < n; i++)
        {
            buckets[nums[i].day & 255]++;
        }
        for (int i = 0; i < 255; i++)
        {
            buckets[i + 1] += buckets[i];
        }
        for (int i = n - 1; i >= 0; i--)
        {
            ans[--buckets[nums[i].day & 255]] = nums[i];
        }
        fill_n(buckets, 256, 0);
        // 15-8 bit
        for (int i = 0; i < n; i++)
        {
            buckets[(ans[i].day >> 8) & 255]++;
        }
        for (int i = 0; i < 255; i++)
        {
            buckets[i + 1] += buckets[i];
        }
        for (int i = n - 1; i >= 0; i--)
        {
            nums[--buckets[(ans[i].day >> 8) & 255]] = ans[i];
        }
        // 23-16 bit
        fill_n(buckets, 256, 0);
        for (int i = 0; i < n; i++)
        {
            buckets[(nums[i].day >> 16) & 255]++;
        }
        for (int i = 0; i < 255; i++)
        {
            buckets[i + 1] += buckets[i];
        }
        for (int i = n - 1; i >= 0; i--)
        {
            ans[--buckets[(nums[i].day >> 16) & 255]] = nums[i];
        }
        // 31-24 bit
        fill_n(buckets, 256, 0);
        for (int i = 0; i < n; i++)
        {
            buckets[(ans[i].day >> 24) & 255]++;
        }
        for (int i = 0; i < 255; i++)
        {
            buckets[i + 1] += buckets[i];
        }
        for (int i = n - 1; i >= 0; i--)
        {
            nums[--buckets[(ans[i].day >> 24) & 255]] = ans[i];
        }
    }

public:
    int countDays(int days, vector<vector<int>> &meetings)
    {
        int n = meetings.size();
        vector<Node> nodes(n << 1);
        int dayBeyondCount = 0;
        for (int i = 0; i < n; i++)
        {
            nodes[i << 1] = {meetings[i][0], 1};
            nodes[(i << 1) + 1] = {meetings[i][1] + 1, -1};
            dayBeyondCount += (meetings[i][1] == days);
        }
        radixSort(nodes);
        int ans = nodes[0].day - 1;
        int meetingCount = 0;
        int i = 0;
        int nodeCount = nodes.size() - dayBeyondCount;
        int firstNoMeetingDay = 0;
        while (i < nodeCount)
        {
            meetingCount += nodes[i].delta;
            while (i < nodeCount - 1 && nodes[i].day == nodes[i + 1].day)
            {
                i++;
                meetingCount += nodes[i].delta;
            }
            if (meetingCount == 0)
            {
                firstNoMeetingDay = nodes[i].day;
            }
            else
            {
                if (firstNoMeetingDay > 0)
                {
                    ans += (nodes[i].day - firstNoMeetingDay);
                    firstNoMeetingDay = 0;
                }
            }
            i++;
        }
        if (firstNoMeetingDay > 0)
        {
            ans += (days - firstNoMeetingDay + 1);
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