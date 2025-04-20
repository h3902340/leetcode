#include <vector>
using namespace std;

class Solution
{
public:
    int numRabbits(vector<int> &answers)
    {
        int n = answers.size();
        int c[1000]{0};
        for (auto a : answers)
        {
            c[a]++;
        }
        int ans = n;
        for (int i = 0; i < 1000; i++)
        {
            int m = c[i] % (i + 1);
            if (m > 0)
            {
                ans += (i + 1 - m);
            }
        }
        return ans;
    }
};

vector<int> answers = {1, 1, 2};

int main()
{
    Solution sol;
    int ans = sol.numRabbits(answers);
    printf("ans = %d\n", ans); // 5
    return 0;
}