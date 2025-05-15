#include <string>
using namespace std;

class Solution
{
public:
    int reverseDegree(string s)
    {
        int sum = 0;
        for (int i = 0; i < s.size(); i++)
        {
            sum += ('z' - s[i] + 1) * (i + 1);
        }
        return sum;
    }
};

string s = "abc";

int main()
{
    Solution sol;
    int ans = sol.reverseDegree(s);
    printf("ans = %d\n", ans); // 148
    return 0;
}