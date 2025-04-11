#include <_printf.h>
#include <vector>
using namespace std;

// TODO: implement the O(log(high)^3) solution
class Solution
{
public:
    int countSymmetricIntegers(int low, int high)
    {
        int ans = 0;
        for (int i = low; i <= high; i++)
        {
            if (i < 100)
            {
                ans += (i % 11 == 0);
            }
            else if (1000 < i && i < 10000)
            {
                div_t d1 = div(i, 10);
                div_t d2 = div(d1.quot, 10);
                div_t d3 = div(d2.quot, 10);
                int l = d3.quot + d3.rem;
                int r = d1.rem + d2.rem;
                ans += (l == r);
            }
        }
        return ans;
    }
};

int low = 1200;
int high = 1230;

int main()
{
    Solution sol;
    int ans = sol.countSymmetricIntegers(low, high);
    printf("ans: %d\n", ans); // 4
    return 0;
}