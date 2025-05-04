#include <vector>
using namespace std;

class Solution
{
public:
    int numEquivDominoPairs(vector<vector<int>> &dominoes)
    {
        int n = dominoes.size();
        int c[10][10]{0};
        int pairs = 0;
        for (int i = 0; i < n; i++)
        {
            int a = dominoes[i][0];
            int b = dominoes[i][1];
            if (a > b)
            {
                swap(a, b);
            }
            if (c[a][b] > 0)
            {
                pairs += c[a][b];
            }
            c[a][b]++;
        }
        return pairs;
    }
};

// 3
vector<vector<int>> dominoes = {{1, 2}, {1, 2}, {1, 1}, {1, 2}, {2, 2}};

int main()
{
    Solution sol;
    int ans = sol.numEquivDominoPairs(dominoes);
    printf("ans = %d\n", ans);
    return 0;
}