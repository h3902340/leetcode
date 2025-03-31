#include <vector>
#include <string>
using namespace std;

class Solution
{
public:
    vector<int> partitionLabels(string s)
    {
        int n = s.size();
        int letterEnd[26]{0};
        for (int i = 0; i < n; i++)
        {
            letterEnd[s[i] - 'a'] = i;
        }
        vector<int> ans;
        int end = letterEnd[s[0] - 'a'];
        int seg = 1;
        for (int i = 1; i < n; ++i)
        {
            if (i > end)
            {
                ans.push_back(seg);
                seg = 0;
            }
            int nextEnd = letterEnd[s[i] - 'a'];
            if (nextEnd > end)
            {
                end = nextEnd;
            }
            ++seg;
        }
        ans.push_back(seg);
        return ans;
    }
};

string s = "ababcbacadefegdehijhklij";

int main()
{
    Solution sol;
    vector<int> ans = sol.partitionLabels(s);
    printf("ans = [%d", ans[0]);
    for (int i = 1; i < ans.size(); i++)
    {
        printf(", %d", ans[i]);
    }
    printf("]\n");
    return 0;
}