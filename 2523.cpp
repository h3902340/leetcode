#include <vector>
using namespace std;

class Solution
{
public:
    int powModulo(int a, int b, int m)
    {
        // return a^b % m
        if (b == 0)
            return 1;
        if (b & 1)
        {
            long temp = powModulo(a, b - 1, m);
            return (a * temp) % m;
        }
        long temp = powModulo(a, b >> 1, m);
        return (temp * temp) % m;
    }
    bool interrogation(int n, int a, int s, int d)
    {
        long temp = powModulo(a, d, n);
        for (int i = 0; i < s; i++)
        {
            if (temp == 1 || temp == n - 1)
            {
                return true;
            }
            temp = (temp * temp) % n;
        }
        return false;
    }
    bool millerTest(int n)
    {
        // n <= 10^6, it's enough to test for only witness 2 and 3
        // (mathematically proven). n-1 = (2^s)*d, a^(n-1) = a^((2^s)*d)
        if (n % 2 == 0)
            return false;
        int s = 0;
        int d = n - 1;
        while (d % 2 == 0)
        {
            s++;
            d >>= 1;
        }
        // when n <= 2047, it's enough to test for only witness 2
        return interrogation(n, 2, s, d) &&
               (n < 2047 || interrogation(n, 3, s, d));
    }
    vector<int> closestPrimes(int left, int right)
    {
        int i = 0;
        int min = INT_MAX;
        int min_i = -1;
        int min_j = -1;
        if (left == 1)
        {
            if (right <= 2)
                return {-1, -1};
            return {2, 3};
        }
        if (left == 2)
        {
            if (right == 2)
                return {-1, -1};
            return {2, 3};
        }
        if (left % 2 == 0)
        {
            left += 1;
        }
        for (int j = left; j <= right; j += 2)
        {
            if (!millerTest(j))
                continue;
            if (i == 0)
            {
                i = j;
                continue;
            }
            if (j - i >= min)
            {
                i = j;
                continue;
            }
            min = j - i;
            min_i = i;
            min_j = j;
            if (min <= 2)
                return {min_i, min_j};
            i = j;
        }
        return {min_i, min_j};
    }
};

int main()
{
    Solution sol;
    vector<int> ans = sol.closestPrimes(19, 31);
    printf("ans = [%d,%d]\n", ans[0], ans[1]); // [29,31]
    return 0;
}