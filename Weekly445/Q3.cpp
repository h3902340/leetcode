#include <string>
#include <vector>
#include <map>
using namespace std;

class Solution
{
public:
    string smallestPalindrome(string s, int k)
    {
        int n = s.size();
        int n_half = n >> 1;
        if (n == 1)
        {
            if (k == 1)
            {
                return s;
            }
            else
            {
                return "";
            }
        }
        int fre[26]{0};
        for (int i = 0; i < n_half; i++)
        {
            fre[s[i] - 'a']++;
        }
        int prod = 1;
        int sum = 0;
        bool isDone = false;
        int i = 25;
        for (; i >= 0; i--)
        {
            if (fre[i])
                break;
        }
        int imax = i;
        int j = 1;
        for (; i >= 0; i--)
        {
            j = 1;
            for (; j <= fre[i]; j++)
            {
                sum++;
                prod = prod * sum / j;
                if (prod > k)
                {
                    prod = prod * j / sum;
                    sum--;
                    isDone = true;
                    break;
                }
                else if (prod == k)
                {
                    isDone = true;
                    break;
                }
            }
            if (isDone)
                break;
        }
        if (i == -1)
            return "";
        string ans(n, 'a');
        int index = 0;
        for (int i2 = 0; i2 < i; i2++)
        {
            for (int j2 = 0; j2 < fre[i2]; j2++)
            {
                ans[index++] += i2;
            }
        }
        for (int j2 = j; j2 < fre[i]; j2++)
        {
            ans[index++] += i;
        }
        fre[i] = j;
        int preChar = i;
        while (k > prod)
        {
            k -= prod;
            int nextChar = preChar + 1;
            for (; nextChar < imax; nextChar++)
            {
                if (fre[nextChar])
                    break;
            }
            prod = prod * fre[nextChar] / fre[preChar];
            preChar = nextChar;
            while (prod > k)
            {
                ans[index++] += preChar;
                fre[preChar]--;
                for (; i < imax; i++)
                {
                    if (fre[i])
                        break;
                }
                preChar = i;
                prod = prod * fre[preChar] / sum;
                sum--;
            }
            if (prod == k)
            {
                ans[index++] += preChar;
                fre[preChar]--;
                break;
            }
        }
        for (int i2 = imax; i2 >= i; i2--)
        {
            for (int j2 = 0; j2 < fre[i2]; j2++)
            {
                ans[index++] += i2;
            }
        }
        if (n & 1)
        {
            ans[index++] = s[n_half];
        }
        for (int i2 = n_half - 1; i2 >= 0; i2--)
        {
            ans[index++] = ans[i2];
        }
        return ans;
    }
};

// string s = "abba"; // "baab"
// int k = 2;

// string s = "aa"; // ""
// int k = 2;

// string s = "bacab"; // "abcba"
// int k = 1;

// string s = "o"; // "o"
// int k = 1;

// string s = "kkkk"; // "kkkk"
// int k = 1;

// string s = "nyggyn"; // "nyggyn"
// int k = 4;

// string s = "daggad"; // "daggad"
// int k = 3;

string s = "oinvvnio"; // "niovvoin"
int k = 7;

int main()
{
    Solution sol;
    string ans = sol.smallestPalindrome(s, k);
    printf("ans = %s\n", ans.c_str());
    return 0;
}