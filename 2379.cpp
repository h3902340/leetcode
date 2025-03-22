#include <string>
using namespace std;

class Solution
{
public:
    int minimumRecolors(string blocks, int k)
    {
        int n = blocks.size();
        int whiteCount = 0;
        for (int i = 0; i < k; i++)
        {
            whiteCount += blocks[i] == 'W';
        }
        int min = whiteCount;
        for (int i = 0; i < n - k; i++)
        {
            whiteCount -= (blocks[i] == 'W');
            whiteCount += (blocks[i + k] == 'W');
            if (whiteCount < min)
            {
                min = whiteCount;
            }
        }
        return min;
    }
};

string blocks = "WBBWWBBWBW";
int k = 7;

int main()
{
    Solution sol;
    int ans = sol.minimumRecolors(blocks, k);
    printf("ans = %d\n", ans);
    return 0;
}