#include <string>
using namespace std;

class Solution
{
public:
    long long numberOfPowerfulInt(long long start, long long finish, int limit, string s)
    {
        long long suffix = atoll(s.c_str());
        if (finish < suffix)
            return 0;
        int n = s.size();
        long long base = fastPow(10, n);
        long long lo = 0;
        if (start < base)
        {
            if (start > suffix)
            {
                lo = 1;
            }
        }
        else
        {
            lo = (start - suffix - 1) / base + 1;
        }
        long long hi = (finish - suffix) / base;
        if (lo == hi)
            return 1;
        if (lo > hi)
            return 0;
        long long ten_d = 1;
        int d = 0;
        while (hi >= ten_d)
        {
            ten_d *= 10;
            d++;
        }
        ten_d /= 10;
        d--;
        lldiv_t hi_div = div(hi, ten_d);
        lldiv_t lo_div = div(lo, ten_d);
        while (ten_d > 1 && hi_div.quot == lo_div.quot)
        {
            ten_d /= 10;
            d--;
            hi = hi_div.rem;
            lo = lo_div.rem;
        }
        if (lo_div.quot > hi_div.quot)
            return 0;
        if (lo_div.quot > limit)
            return 0;
        bool isLowEnd = false;
        bool isHighEnd = false;
        int high = hi_div.quot;
        if (hi_div.quot > limit)
        {
            high = limit;
            isHighEnd = true;
        }
        if (ten_d == 1)
            return high - lo_div.quot + 1;
        high += isHighEnd;
        long long ans = 0;
        long long exp = fastPow(limit + 1, d);
        if (high > lo_div.quot + 1)
        {
            ans += exp * (high - lo_div.quot - 1);
        }
        lo = lo_div.rem;
        hi = hi_div.rem;
        ten_d /= 10;
        exp /= (limit + 1);
        while (ten_d >= 1)
        {
            hi_div = div(hi, ten_d);
            lo_div = div(lo, ten_d);

            if (isHighEnd)
            {
                high = 0;
            }
            else
            {
                high = hi_div.quot;
                if (hi_div.quot > limit)
                {
                    high = limit + 1;
                    isHighEnd = true;
                }
            }
            int low = 0;
            if (!isLowEnd)
            {
                if (limit < lo_div.quot)
                {
                    isLowEnd = true;
                }
                else
                {
                    low = limit - lo_div.quot;
                }
            }
            ans += exp * (high + low);
            if (isHighEnd && isLowEnd)
                break;
            lo = lo_div.rem;
            hi = hi_div.rem;
            ten_d /= 10;
            exp /= (limit + 1);
        }
        ans += !isLowEnd + !isHighEnd;
        return ans;
    }

private:
    long long fastPow(int a, int b)
    {
        return fastPowInternal(a, b, 1);
    }
    long long fastPowInternal(long long a, int b, long long v)
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

long long start = 123546;
long long finish = 32486458654;
int limit = 4;
string s = "1";

int main()
{
    Solution sol;
    long long ans = sol.numberOfPowerfulInt(start, finish, limit, s);
    printf("ans = %lld\n", ans); // 7030275
    return 0;
}