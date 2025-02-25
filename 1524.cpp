#include <vector>
using namespace std;

class Solution
{
public:
    int numOfSubarrays(vector<int> &arr)
    {
        int n = arr.size();
        long numOdd = arr[0] & 1;
        for (int i = 1; i < n; ++i)
        {
            arr[i] += arr[i - 1];
            numOdd += arr[i] & 1;
        }
        return ((n - numOdd + 1) * numOdd) % 1000000007;
    }
};

vector<int> arr = {1, 3, 5};

int main()
{
    Solution sol;
    int ans = sol.numOfSubarrays(arr);
    printf("ans = %d\n", ans);
    return 0;
}