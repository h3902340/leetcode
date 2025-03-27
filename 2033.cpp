#include <vector>
#include <stdlib.h>
using namespace std;

class Solution
{
public:
    int minOperations(vector<vector<int>> &grid, int x)
    {
        int m = grid.size();
        int n = grid[0].size();
        int counter[10001]{0};
        int min = 10001;
        int max = 0;
        int rem = grid[0][0] % x;
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                div_t result = div(grid[i][j], x);
                if (result.rem != rem)
                    return -1;
                counter[result.quot]++;
                if (result.quot < min)
                {
                    min = result.quot;
                }
                if (result.quot > max)
                {
                    max = result.quot;
                }
            }
        }
        int halfSize = (m * n - 1) >> 1;
        int sum = 0;
        int med = 0;
        for (int i = min; i <= max; i++)
        {
            sum += counter[i];
            if (sum > halfSize)
            {
                med = i;
                break;
            }
        }
        int ans = 0;
        for (int i = min; i < med; i++)
        {
            ans += (med - i) * counter[i];
        }
        for (int i = med + 1; i <= max; i++)
        {
            ans += (i - med) * counter[i];
        }
        return ans;
    }
};

vector<vector<int>> grid = {{931, 128}, {639, 712}};
int x = 73;

int main()
{
    Solution sol;
    int ans = sol.minOperations(grid, x);
    printf("ans = %d\n", ans); // 12
    return 0;
}