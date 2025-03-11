#include <vector>
using namespace std;

class Solution
{
public:
    int getIndex(char c)
    {
        switch (c)
        {
        case 'a':
            return 0;
        case 'e':
            return 1;
        case 'i':
            return 2;
        case 'o':
            return 3;
        case 'u':
            return 4;
        default: // consonant
            return 5;
        }
    }
    long long atLeastKConsonant(string word, int k)
    {
        int n = word.size();
        int i = 0;
        long long num = 0;
        int charCount[6]{0};
        for (int j = 0; j < n; j++)
        {
            charCount[getIndex(word[j])]++;
            int iOld = i;
            while (charCount[0] && charCount[1] && charCount[2] && charCount[3] && charCount[4] && charCount[5] >= k)
            {
                charCount[getIndex(word[i])]--;
                i++;
            }
            num += (i - iOld) * (n - j);
        }
        return num;
    }
    long long countOfSubstrings(string word, int k)
    {
        return atLeastKConsonant(word, k) - atLeastKConsonant(word, k + 1);
    }
};

string word = "ieaouqqieaouqq";
int k = 1;

int main()
{
    Solution sol;
    int ans = sol.countOfSubstrings(word, k);
    printf("ans = %d\n", ans); // 3
    return 0;
}