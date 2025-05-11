#include <vector>
using namespace std;

class Solution {
   public:
    int minDeletion(string s, int k) {
        vector<int> fre(26);
        for (int i = 0; i < s.size(); i++) {
            fre[s[i] - 'a']++;
        }
        sort(fre.begin(), fre.end());
        int ans = 0;
        for (int i = 25; i >= 0; i--) {
            if (fre[i]) {
                if (k > 0) {
                    k--;
                } else {
                    ans += fre[i];
                }
            }
        }
        return ans;
    }
};

// 0
string s = "aabb";
int k = 2;

int main() {
    Solution sol;
    int ans = sol.minDeletion(s, k);
    printf("ans = %d\n", ans);
    return 0;
}