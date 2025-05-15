#include <vector>
using namespace std;

class Solution {
   public:
    int maxFreqSum(string s) {
        int fre[26]{0};
        for (int i = 0; i < s.size(); i++) {
            fre[s[i] - 'a']++;
        }
        int maxV = fre[0];
        if (maxV < fre['e' - 'a']) {
            maxV = fre['e' - 'a'];
        }
        if (maxV < fre['i' - 'a']) {
            maxV = fre['i' - 'a'];
        }
        if (maxV < fre['o' - 'a']) {
            maxV = fre['o' - 'a'];
        }
        if (maxV < fre['u' - 'a']) {
            maxV = fre['u' - 'a'];
        }
        int maxC = 0;
        for (int i = 0; i < 26; i++) {
            if (i == 0 || i == 'e' - 'a' || i == 'i' - 'a' || i == 'o' - 'a' ||
                i == 'u' - 'a')
                continue;
            if (maxC < fre[i]) {
                maxC = fre[i];
            }
        }
        return maxV + maxC;
    }
};

// 6
string s = "successes";

int main() {
    Solution sol;
    int ans = sol.maxFreqSum(s);
    printf("ans = %d\n", ans);
    return 0;
}