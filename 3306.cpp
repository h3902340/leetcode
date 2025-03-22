#include <vector>
using namespace std;

class Solution
{
public:
    long long countOfSubstrings(string word, int k)
    {
        int n = word.size();
        int i = 0;
        long long num = 0;
        int charCount[128]{0};
        bool isVowel[128]{false};
        isVowel['a'] = true;
        isVowel['e'] = true;
        isVowel['i'] = true;
        isVowel['o'] = true;
        isVowel['u'] = true;
        int vowelCount = 0;
        int consonantCount = 0;
        int bonus = 1;
        for (int j = 0; j < n; j++)
        {
            if (isVowel[word[j]])
            {
                vowelCount += (charCount[word[j]] == 0);
            }
            else
            {
                consonantCount++;
            }
            while (consonantCount > k)
            {
                charCount[word[i]]--;
                if (isVowel[word[i]])
                {
                    vowelCount -= (charCount[word[i]] == 0);
                }
                else
                {
                    consonantCount--;
                }
                i++;
                bonus = 1;
            }
            charCount[word[j]]++;
            if (consonantCount == k && vowelCount == 5)
            {
                while (isVowel[word[i]] && charCount[word[i]] > 1)
                {
                    charCount[word[i]]--;
                    i++;
                    bonus++;
                }
                num += bonus;
            }
        }
        return num;
    }
};

string word = "buiaceobubuufaaofoaooeief";
int k = 2;

int main()
{
    Solution sol;
    int ans = sol.countOfSubstrings(word, k);
    printf("ans = %d\n", ans); // 8
    return 0;
}