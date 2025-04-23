#include <_printf.h>

int a[5][37]{0};
int b[6]{0};
bool isInit = false;

static void init()
{
    if (isInit)
        return;
    a[0][0] = 1;
    b[0] = 1;
    for (int i = 1; i < 5; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            for (int k = 0; k <= (i - 1) * 9; k++)
            {
                a[i][k + j] += a[i - 1][k];
            }
        }
        b[i] = b[i - 1] * 10;
    }
    b[5] = b[4] * 10;
    isInit = true;
}

class Solution
{
public:
    int countLargestGroup(int n)
    {
        init();
        int set[37]{0};
        int d = 1;
        int c = 0;
        while (n >= d)
        {
            d *= 10;
            c++;
        }
        int e = 0;
        while (n > 0)
        {
            while (n < b[c])
            {
                c--;
            }
            n -= b[c];
            for (int i = 0; i <= c * 9; i++)
            {
                set[i + e] += a[c][i];
            }
            e++;
        }
        set[e]++;
        int maxGroupCount = 0;
        int max = 0;
        for (int i = 1; i < 37; i++)
        {
            if (set[i] > max)
            {
                max = set[i];
                maxGroupCount = 1;
            }
            else if (set[i] == max)
            {
                maxGroupCount++;
            }
        }
        return maxGroupCount;
    }
};

int n = 13; // 4

int main()
{
    Solution sol;
    int ans = sol.countLargestGroup(n);
    printf("ans = %d\n", ans);
    return 0;
}