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
        int characterCount[3]{0};
        for (int j = 0; j < n; j++)
        {
            characterCount[s[j] - 'a']++;
            int endMargin = n - j;
            while (characterCount[0] > 0 && characterCount[1] > 0 &&
                   characterCount[2] > 0)
            {
                num += endMargin;
                characterCount[s[i] - 'a']--;
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