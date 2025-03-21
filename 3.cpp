#include <string>
#include <unordered_set>
using namespace std;

class Solution
{
public:
    int lengthOfLongestSubstring(string s)
    {
        int n = s.size();
        vector<int> lastOccurance(256, -1);
        int i = 0;
        int max = 0;
        for (int j = 0; j < n; j++)
        {
            if (lastOccurance[s[j]] >= i)
            {
                i = lastOccurance[s[j]] + 1;
            }
            lastOccurance[s[j]] = j;
            int current = j - i + 1;
            if (current > max)
            {
                max = current;
            }
        }
        return max;
    }
};

string s = "abcabcbb";

int main()
{
    Solution sol;
    int ans = sol.lengthOfLongestSubstring(s);
    printf("ans = %d\n", ans); // 3
    return 0;
}