#include <string>
using namespace std;

class Solution
{
public:
    string pushDominoes(string dominoes)
    {
        int n = dominoes.size();
        int j = 0;
        bool leftIsR = false;
        for (int i = 0; i < n; i++)
        {
            switch (dominoes[i])
            {
            case 'L':
                if (leftIsR)
                {
                    int m = (i + j) >> 1;
                    bool isOdd = (i - j) & 1;
                    for (; j < m; j++)
                    {
                        dominoes[j] = 'R';
                    }
                    if (isOdd)
                    {
                        j++;
                    }
                    for (; j < i; j++)
                    {
                        dominoes[j] = 'L';
                    }
                }
                else
                {
                    for (; j < i; j++)
                    {
                        dominoes[j] = 'L';
                    }
                }
                leftIsR = false;
                break;
            case 'R':
                if (leftIsR)
                {
                    for (; j < i; j++)
                    {
                        dominoes[j] = 'R';
                    }
                }
                else
                {
                    j = i;
                }
                leftIsR = true;
                break;
            default:
                continue;
            }
            j++;
        }
        if (j < n)
        {
            if (leftIsR)
            {
                for (; j < n; j++)
                {
                    dominoes[j] = 'R';
                }
            }
        }
        return dominoes;
    }
};

// "LL.RR.LLRRLL.."
string dominoes = ".L.R...LR..L..";

int main()
{
    Solution sol;
    string ans = sol.pushDominoes(dominoes);
    printf("ans = %s\n", ans.c_str());
    return 0;
}