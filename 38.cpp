#include <string>
using namespace std;

class Solution
{
public:
    string countAndSay(int n)
    {
        if (n == 1)
            return "1";
        return runLengthEncoding(countAndSay(n - 1));
    }

private:
    string runLengthEncoding(string s)
    {
        string o = "";
        for (int i = 0; i < s.size(); i++)
        {
            int c = 1;
            while (i + 1 < s.size() && s[i] == s[i + 1])
            {
                c++;
                i++;
            }
            o += (c + '0');
            o += s[i];
        }
        return o;
    }
};

int n = 4;

int main()
{
    Solution sol;
    string ans = sol.countAndSay(n);
    printf("ans = %s\n", ans.c_str());
    return 0;
}