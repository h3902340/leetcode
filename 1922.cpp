#include <_printf.h>
class Solution
{
public:
    int countGoodNumbers(long long n)
    {
        const int m = 1000000007;
        long long ans = powModulo(20, n >> 1, m);
        if (n & 1)
        {
            ans = (ans * 5) % m;
        }
        return ans;
    }

private:
    long long powModulo(int a, long long b, int m)
    {
        if (b == 0)
            return 1;
        if (b & 1)
        {
            return (powModulo(a, b - 1, m) * a) % m;
        }
        long long temp = powModulo(a, b >> 1, m);
        return (temp * temp) % m;
    }
};

long long n = 50;

int main()
{
    Solution sol;
    int ans = sol.countGoodNumbers(n);
    printf("ans = %d\n", ans); // 564908303
    return 0;
}