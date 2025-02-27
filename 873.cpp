#include <vector>
using namespace std;

class Solution
{
public:
    int lenLongestFibSubseq(vector<int> &arr)
    {
        int n = arr.size();
        int max = 2;
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                int left = j + 1;
                int right = n - 1;
                int firstTerm = arr[i];
                int secondTerm = arr[j];
                int sequenceLength = 2;
                while (left <= right)
                {
                    int mid = (left + right) >> 1;
                    int target = firstTerm + secondTerm;
                    if (arr[mid] == target)
                    {
                        left = mid + 1;
                        right = n - 1;
                        firstTerm = secondTerm;
                        secondTerm = arr[mid];
                        sequenceLength++;
                    }
                    else if (arr[mid] > target)
                    {
                        right = mid - 1;
                    }
                    else
                    {
                        left = mid + 1;
                    }
                }
                if (sequenceLength > max)
                {
                    max = sequenceLength;
                }
            }
        }
        if (max == 2)
        {
            return 0;
        }
        else
        {
            return max;
        }
    }
};

vector<int> arr = {1, 3, 7, 11, 12, 14, 18};

int main()
{
    Solution sol;
    int ans = sol.lenLongestFibSubseq(arr);
    printf("ans = %d", ans); // expecting 3
    return 0;
}