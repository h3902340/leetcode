#include <_printf.h>

const int M = 10001;
const int DMAX = 14;
const int NMAX = 10000 - 1 + DMAX;
const int MOD = 1000000007;
int C[NMAX][DMAX];
int prime[25];
bool isInit = false;
static void init()
{
    if (isInit)
        return;
    for (int i = 1; i < NMAX; i++)
    {
        C[i][0] = 1;
        int cap = i;
        if (i + 1 > DMAX)
        {
            cap = DMAX;
        }
        else
        {
            C[i][i] = 1;
        }
        for (int j = 1; j < cap; j++)
        {
            C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
            if (C[i][j] >= MOD)
            {
                C[i][j] -= MOD;
            }
        }
    }
    const int cap1 = 10;
    const int cap2 = 100;
    int sieve[cap2]{0};
    int index = 0;
    for (int i = 2; i < cap1; i++)
    {
        if (sieve[i] == 0)
        {
            for (int j = i << 1; j < cap2; j += i)
            {
                sieve[j] = 1;
            }
            prime[index++] = i;
        }
    }
    for (int i = cap1 + 1; i < cap2; i++)
    {
        if (sieve[i] == 0)
        {
            prime[index++] = i;
        }
    }
    isInit = true;
}

class Solution
{
public:
    int idealArrays(int n, int maxValue)
    {
        init();
        int dp[M]{0};
        dp[1] = 1;
        int ans = 1;
        for (int j = 2; j <= maxValue; j++)
        {
            int num = j;
            long long way = 1;
            for (auto p : prime)
            {
                int d = 0;
                while (num % p == 0)
                {
                    num /= p;
                    d++;
                }
                if (d > 0)
                {
                    way = way * C[n + d - 1][d] % MOD;
                }
                if (dp[num])
                {
                    way = way * dp[num] % MOD;
                    num = 1;
                    break;
                }
            }
            if (num > 1)
            {
                way = way * n % MOD;
            }
            dp[j] = way;
            ans += way;
            if (ans >= MOD)
            {
                ans -= MOD;
            }
        }
        return ans;
    }
};

// int n = 2; // 10
// int maxValue = 5;

// int n = 5; // 11
// int maxValue = 3;

int n = 184; // 510488787
int maxValue = 389;

// int n = 5878; // 465040898
// int maxValue = 2900;

int main()
{
    Solution sol;
    int ans = sol.idealArrays(n, maxValue);
    printf("ans = %d\n", ans);
    return 0;
}