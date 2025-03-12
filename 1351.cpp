#include <vector>
using namespace std;

class Solution
{
public:
    // Young tableau
    int countNegatives(vector<vector<int>> &grid)
    {
        int m = grid.size();
        int n = grid[0].size();
        int i = 0;
        int j = n - 1;
        int num = 0;
        while (i < m && j >= 0)
        {
            if (grid[i][j] < 0)
            {
                num += (m - i);
                j--;
            }
            else
            {
                i++;
            }
        }
        return num;
    }
};

vector<vector<int>> grid = {{4, 3, 2, -1}, {3, 2, 1, -1}, {1, 1, -1, -2}, {-1, -1, -2, -3}};

int main()
{
    Solution sol;
    int ans = sol.countNegatives(grid);
    printf("ans = %d\n", ans); // 8
    return 0;
}