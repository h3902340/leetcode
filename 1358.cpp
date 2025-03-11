#include <string>
using namespace std;

class Solution
{
public:
    int numberOfSubstrings(string s)
    {
        int n = s.size();
        int i = 0;
        int num = 0;
        int charCount[3]{0};
        for (int j = 0; j < n; j++)
        {
            charCount[s[j] - 'a']++;
            int endMargin = n - j;
            while (charCount[0] && charCount[1] && charCount[2])
            {
                num += endMargin;
                charCount[s[i] - 'a']--;
                i++;
            }
        }
        return num;
    }
};

string s = "abcabc";

int main()
{
    Solution sol;
    int ans = sol.numberOfSubstrings(s);
    printf("ans = %d\n", ans); // 10
    return 0;
}