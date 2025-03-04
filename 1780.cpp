#include <vector>
using namespace std;

class Solution
{
public:
    bool checkPowersOfThree(int n)
    {
        return n % 3 == 2 ? false : (n == 0 ? true : checkPowersOfThree(n / 3));
    }
};

int n = 21;

int main()
{
    Solution sol;
    bool ans = sol.checkPowersOfThree(n);
    printf("ans = %d\n", ans); // 0 expected
    return 0;
}