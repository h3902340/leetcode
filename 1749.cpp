#include <vector>
using namespace std;

class Solution
{
public:
    int maxAbsoluteSum(vector<int> &nums)
    {
        int max = INT_MIN;
        int currentMax = 0;
        int currentMin = 0;
        for (int i : nums)
        {
            currentMax += i;
            currentMin += i;
            if (i > currentMax)
            {
                currentMax = i;
            }
            if (i < currentMin)
            {
                currentMin = i;
            }
            if (abs(currentMax) > max)
            {
                max = abs(currentMax);
            }
            if (abs(currentMin) > max)
            {
                max = abs(currentMin);
            }
        }
        return max;
    }
};