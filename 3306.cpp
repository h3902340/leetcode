#include <vector>
#include <queue>
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
        int consonantCount = 0;
        bool isVowel[128]{false};
        isVowel['a'] = true;
        isVowel['e'] = true;
        isVowel['i'] = true;
        isVowel['o'] = true;
        isVowel['u'] = true;
        queue<int> consonantQueue;
        int firstRightConsonant = -1;
        for (int j = 0; j < n; j++)
        {
            if (!isVowel[word[j]])
            {
                consonantQueue.push(j);
                if (consonantCount == k)
                {
                    while (i < consonantQueue.front() + 1)
                    {
                        charCount[word[i]]--;
                        i++;
                    }
                    consonantQueue.pop();
                }
                else
                {
                    consonantCount++;
                }
            }
            charCount[word[j]]++;
            int iOld = i;
            while (charCount['a'] && charCount['e'] && charCount['i'] &&
                   charCount['o'] && charCount['u'] && consonantCount == k)
            {
                charCount[word[i]]--;
                consonantCount -= !isVowel[word[i]];
                i++;
            }
            if (i > iOld)
            {
                if (consonantCount == k - 1)
                {
                    consonantQueue.pop();
                }
                int jNew = j + 1;
                if (firstRightConsonant == -1 || jNew > firstRightConsonant)
                {
                    while (jNew < n && isVowel[word[jNew]])
                    {
                        jNew++;
                    }
                    firstRightConsonant = jNew;
                }
                else
                {
                    jNew = firstRightConsonant;
                }
                num += (i - iOld) * (jNew - j);
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