#include <vector>
using namespace std;

class Solution
{
public:
    int maximumCandies(vector<int> &candies, long long k)
    {
        int n = candies.size();
        int l = 1;
        long r = 0;
        // O(n)
        for (int i = 0; i < n; i++)
        {
            r += candies[i];
        }
        r /= k;
        int max = 0;
        int mid = 0;
        long long pileCount = 0;
        bool isSatisfied = false;
        // total time: O(nlog(max(candies)))
        // O(log(max(candies))) times
        while (l <= r)
        {
            mid = (l + r) >> 1;
            pileCount = 0;
            isSatisfied = false;
            // O(n)
            for (int i = 0; i < n; i++)
            {
                pileCount += candies[i] / mid;
                if (pileCount < k)
                    continue;
                isSatisfied = true;
                if (mid > max)
                {
                    max = mid;
                }
                break;
            }
            if (isSatisfied)
            {
                l = mid + 1;
            }
            else
            {
                r = mid - 1;
            }
        }
        return max;
    }
};

vector<int> candies = {5, 8, 6};
int k = 3;

int main()
{
    Solution sol;
    int ans = sol.maximumCandies(candies, k);
    printf("ans = %d\n", ans); // 5
    return 0;
}