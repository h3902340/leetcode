#include <vector>
using namespace std;

class Solution
{
public:
    int minDominoRotations(vector<int> &tops, vector<int> &bottoms)
    {
        int n = tops.size();
        int a = topToBot(tops, bottoms, n);
        if (a == -1)
        {
            if (tops[0] == bottoms[0])
            {
                return -1;
            }
            else
            {
                return topToBot(bottoms, tops, n);
            }
        }
        return a;
    }

private:
    int topToBot(vector<int> &tops, vector<int> &bottoms, int n)
    {
        int top = tops[0];
        int bot = bottoms[0];
        int a = 0;
        int b = 0;
        if (top != bot)
        {
            a = 1;
        }
        for (int i = 1; i < n; i++)
        {
            if (tops[i] == top)
            {
                if (bottoms[i] != top)
                {
                    a++;
                }
            }
            else
            {
                if (bottoms[i] == top)
                {
                    b++;
                }
                else
                {
                    return -1;
                }
            }
        }
        return a < b ? a : b;
    }
};

vector<int> tops = {2, 1, 2, 4, 2, 2}; // 2
vector<int> bottoms = {5, 2, 6, 2, 3, 2};

int main()
{
    Solution sol;
    int ans = sol.minDominoRotations(tops, bottoms);
    printf("ans = %d\n", ans);
    return 0;
}