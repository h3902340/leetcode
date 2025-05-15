#include <vector>
using namespace std;

const int A = 0;
const int E = 'e' - 'a';
const int I = 'i' - 'a';
const int O = 'o' - 'a';
const int U = 'u' - 'a';

class Solution {
   public:
    int maxFreqSum(string s) {
        int fre[26]{0};
        for (int i = 0; i < s.size(); i++) {
            fre[s[i] - 'a']++;
        }
        int maxV = fre[A];
        if (maxV < fre[E]) {
            maxV = fre[E];
        }
        if (maxV < fre[I]) {
            maxV = fre[I];
        }
        if (maxV < fre[O]) {
            maxV = fre[O];
        }
        if (maxV < fre[U]) {
            maxV = fre[U];
        }
        int maxC = 0;
        for (int i = 0; i < 26; i++) {
            if (i == A || i == E || i == I || i == O || i == U) continue;
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