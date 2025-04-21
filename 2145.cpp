#include <vector>
using namespace std;

class Solution
{
public:
    int numberOfArrays(vector<int> &differences, int lower, int upper)
    {
        int n = differences.size();
        long long min = differences[0];
        long long max = differences[0];
        long long tmp = differences[0];
        for (int i = 1; i < n; i++)
        {
            tmp += differences[i];
            if (tmp > max)
            {
                max = tmp;
            }
            else if (tmp < min)
            {
                min = tmp;
            }
        }
        min = lower - min;
        max = upper - max;
        if (min < lower)
        {
            min = lower;
        }
        if (max > upper)
        {
            max = upper;
        }
        if (min > max)
        {
            return 0;
        }
        else
        {
            return max - min + 1;
        }
    }
};

vector<int> differences = {3, -4, 5, 1, -2}; // 4
int lower = -4;
int upper = 5;

int main()
{
    Solution sol;
    int ans = sol.numberOfArrays(differences, lower, upper);
    printf("ans = %d\n", ans);
    return 0;
}