#include <vector>
using namespace std;

class Solution
{
public:
    int countGoodTriplets(vector<int> &arr, int a, int b, int c)
    {
        int n = arr.size();
        int ans = 0;
        vector<int> prefixSum(1001, 0);
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                if (arr[i] - arr[j] > b || arr[j] - arr[i] > b)
                    continue;
                int lmin = arr[i] - a;
                int lmax = arr[i] + a;
                int rmin = arr[j] - c;
                int rmax = arr[j] + c;
                int l = lmin;
                if (l < rmin)
                {
                    l = rmin;
                }
                if (l < 0)
                {
                    l = 0;
                }
                int r = rmax;
                if (r > lmax)
                {
                    r = lmax;
                }
                if (r > 1000)
                {
                    r = 1000;
                }
                if (l <= r)
                {
                    if (l == 0)
                    {
                        ans += prefixSum[r];
                    }
                    else
                    {
                        ans += prefixSum[r] - prefixSum[l - 1];
                    }
                }
            }
            for (int j = arr[i]; j < 1001; j++)
            {
                prefixSum[j]++;
            }
        }
        return ans;
    }
};

vector<int> arr = {3, 0, 1, 1, 9, 7};
int a = 7;
int b = 2;
int c = 3;

int main()
{
    Solution sol;
    int ans = sol.countGoodTriplets(arr, a, b, c);
    printf("ans = %d\n", ans); // 4
    return 0;
}