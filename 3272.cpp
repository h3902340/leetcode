#include <_printf.h>
#include <unordered_set>
using namespace std;

class Solution
{
public:
    long long countGoodIntegers(int n, int k)
    {
        int fac[11];
        int f = 1;
        fac[0] = f;
        for (int i = 1; i < 11; i++)
        {
            f *= i;
            fac[i] = f;
        }
        bool isOdd = false;
        if (n & 1)
        {
            n >>= 1;
            isOdd = true;
        }
        else
        {
            n = (n >> 1) - 1;
        }
        long long ans = 0;
        int lo = fastPow(10, n);
        int hi = lo * 10;
        for (int i = lo; i < hi; i++)
        {
            int digits[10]{0};
            int fre[10]{0};
            int size = 0;
            int q = i / 10;
            int r = i % 10;
            digits[size++] = r;
            fre[r]++;
            while (q > 0)
            {
                r = q % 10;
                q = q / 10;
                digits[size++] = r;
                fre[r]++;
            }
            int temp = size;
            long dividend = i;
            if (isOdd)
            {
                for (int j = 1; j < temp; j++)
                {
                    digits[size++] = digits[j];
                    fre[digits[j]]++;
                    dividend = dividend * 10 + digits[j];
                }
            }
            else
            {
                for (int j = 0; j < temp; j++)
                {
                    digits[size++] = digits[j];
                    fre[digits[j]]++;
                    dividend = dividend * 10 + digits[j];
                }
            }
            long freToLong = 0;
            long m = 1;
            for (int j = 0; j < 10; j++)
            {
                freToLong += m * fre[j];
                m *= 10;
            }
            if (dividend % k || seen.count(freToLong))
            {
                continue;
            }
            seen.insert(freToLong);
            long long c = fac[size];
            for (int j = 0; j < 10; j++)
            {
                c /= fac[fre[j]];
            }
            c = c * (size - fre[0]) / size;
            ans += c;
        }
        return ans;
    }

private:
    unordered_set<long> seen;
    int fastPow(int a, int b)
    {
        return fastPowInternal(a, b, 1);
    }
    int fastPowInternal(int a, int b, int v)
    {
        if (b == 0)
            return v;
        if (b & 1)
        {
            return fastPowInternal(a, b - 1, v * a);
        }
        return fastPowInternal(a * a, b >> 1, v);
    }
};

int n = 5;
int k = 6;

int main()
{
    Solution sol;
    long long ans = sol.countGoodIntegers(n, k);
    printf("ans = %lld\n", ans); // 27
    return 0;
}