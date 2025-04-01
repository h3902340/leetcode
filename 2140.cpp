#include <vector>
using namespace std;

class Solution
{
public:
    long long mostPoints(vector<vector<int>> &questions)
    {
        int n = questions.size();
        vector<long long> table(n);
        table[n - 1] = questions[n - 1][0];
        for (int i = n - 2; i >= 0; i--)
        {
            if (i + questions[i][1] + 1 >= n)
            {
                if (questions[i][0] > table[i + 1])
                {
                    table[i] = questions[i][0];
                }
                else
                {
                    table[i] = table[i + 1];
                }
            }
            else
            {
                long long a = questions[i][0] + table[i + questions[i][1] + 1];
                if (a > table[i + 1])
                {
                    table[i] = a;
                }
                else
                {
                    table[i] = table[i + 1];
                }
            }
        }
        return table[0];
    }
};

vector<vector<int>> questions = {{3, 2}, {4, 3}, {4, 4}, {2, 5}};

int main()
{
    Solution sol;
    long long ans = sol.mostPoints(questions);
    printf("ans = %lld\n", ans);
    return 0;
}
