#include <vector>
using namespace std;

class Solution
{
public:
    int KMP(string str1, string str2, int n1, int n2, vector<int> failure2)
    {
        int i = 0;
        int j = 0;
        while (i < n1)
        {
            if (str1[i] == str2[j])
            {
                i++;
                j++;
                if (j == n2)
                {
                    return j;
                }
            }
            else
            {
                j = failure2[j];
                if (j == -1)
                {
                    i++;
                    j++;
                }
            }
        }
        return j;
    }
    vector<int> failureFunction(string pattern, int n)
    {
        vector<int> failure(n + 1);
        failure[0] = -1;
        failure[1] = 0;
        int i = 1;
        int j = 0;
        while (i < n)
        {
            if (pattern[j] == pattern[i])
            {
                i++;
                failure[i] = j++;
            }
            else if (j > 0)
            {
                j = failure[j];
            }
            else
            {
                i++;
                failure[i] = 0;
            }
        }
        return failure;
    }
    string shortestCommonSupersequence(string str1, string str2)
    {
        int n1 = str1.length();
        int n2 = str2.length();
        vector<int> failure1 = failureFunction(str1, n1);
        vector<int> failure2 = failureFunction(str2, n2);
        int common1 = KMP(str1, str2, n1, n2, failure2);
        int common2 = KMP(str2, str1, n2, n1, failure1);
        if (str1 > str2)
        {
            if (common1 == n2)
            {
                return str1;
            }
        }
        else
        {
            if (common2 == n1)
            {
                return str2;
            }
        }
        if (common1 > common2)
        {
            return str1.substr(0, n1 - common1) + str2;
        }
        else
        {
            return str2.substr(0, n2 - common2) + str1;
        }
    }
};

string str1 = "abac";
string str2 = "cab";
// string str1 = "abcdcda";
// string str2 = "cdca";

int main()
{
    Solution sol;
    string ans = sol.shortestCommonSupersequence(str1, str2);
    printf("ans = %s\n", ans.c_str());
    return 0;
}