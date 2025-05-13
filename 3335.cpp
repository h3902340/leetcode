#include <string>
using namespace std;

const int MOD = 1e9 + 7;
const int ALPHABET_SIZE = 26;
int fre[ALPHABET_SIZE];

class Solution {
   public:
    int lengthAfterTransformations(string s, int t) {
        int n = s.size();
        int q = t / ALPHABET_SIZE;
        int r = t % ALPHABET_SIZE;
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            fre[i] = 0;
        }
        for (int i = 0; i < n; i++) {
            int j = s[i] - 'a' + r;
            if (j < ALPHABET_SIZE) {
                fre[j]++;
            } else {
                fre[j - ALPHABET_SIZE]++;
                fre[j - ALPHABET_SIZE + 1]++;
            }
        }
        while (q > 0) {
            int z_count = fre[ALPHABET_SIZE - 1];
            for (int i = ALPHABET_SIZE - 1; i >= 1; i--) {
                fre[i] += fre[i - 1];
                if (fre[i] >= MOD) {
                    fre[i] -= MOD;
                }
            }
            fre[0] += z_count;
            if (fre[0] >= MOD) {
                fre[0] -= MOD;
            }
            fre[1] += z_count;
            if (fre[1] >= MOD) {
                fre[1] -= MOD;
            }
            q--;
        }
        int ans = fre[0];
        for (int i = 1; i < ALPHABET_SIZE; i++) {
            ans += fre[i];
            if (ans >= MOD) {
                ans -= MOD;
            }
        }
        return ans;
    }
};

// 2
string s = "abcyy";
int t = 2;

int main() {
    Solution sol;
    int ans = sol.lengthAfterTransformations(s, t);
    printf("ans = %d\n", ans);
    return 0;
}