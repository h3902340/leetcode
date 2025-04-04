#include <vector>
using namespace std;

struct Line
{
    long a;
    long b;
    Line(long a, long b) : a(a), b(b) {}
    Line() : a(0), b(0) {}
};
struct RationalPoint
{
    long x;
    long y;
    long d;
    RationalPoint(long x, long y, long d) : x(x), y(y), d(d) {}
    RationalPoint() : x(0), y(0), d(0) {}
};
class Solution
{
public:
    long long minimumCost(vector<int> &nums, vector<int> &cost, int k)
    {
        int n = nums.size();
        for (int i = 1; i < n; i++)
        {
            nums[i] += nums[i - 1];
            cost[i] += cost[i - 1];
        }
        nums.insert(nums.begin(), 0);
        cost.insert(cost.begin(), 0);
        Line lines[1000];
        RationalPoint points[1000];
        int lineTop = -1;
        int pointTop = -1;
        long long ans = 0;
        for (int i = n; i >= 1; i--)
        {
            long a = -nums[i];
            long b = (long)nums[i] * cost[i] + ans + k * (cost[n] - cost[i]);
            if (lineTop == -1)
            {
                lines[0].a = a;
                lines[0].b = b;
                lineTop = 0;
            }
            else
            {
                if (pointTop != -1)
                {
                    RationalPoint p = points[pointTop];
                    while (a * p.x + b * p.d < p.y)
                    {
                        pointTop--;
                        lineTop--;
                        if (pointTop == -1)
                            break;
                        p = points[pointTop];
                    }
                }
                Line l = lines[lineTop];
                pointTop++;
                points[pointTop].x = l.b - b;
                points[pointTop].y = a * l.b - l.a * b;
                points[pointTop].d = a - l.a;
                lineTop++;
                lines[lineTop].a = a;
                lines[lineTop].b = b;
            }
            int l = 0;
            int r = pointTop;
            int x = cost[i - 1];
            int min = lineTop;
            while (l <= r)
            {
                int mid = (l + r) >> 1;
                if (points[mid].x < x * points[mid].d)
                {
                    r = mid - 1;
                    min = mid;
                }
                else
                {
                    l = mid + 1;
                }
            }
            ans = lines[min].a * x + lines[min].b;
        }
        return ans + k * cost[n];
    }
};

vector<int> nums = {648, 453, 956, 545, 348, 129, 886, 944, 327, 208, 871};
vector<int> cost = {879, 917, 677, 565, 753, 907, 553, 756, 434, 935, 738};
int k = 74;

int main()
{
    Solution sol;
    long long ans = sol.minimumCost(nums, cost, k);
    printf("ans = %lld\n", ans); // 30398493
    return 0;
}