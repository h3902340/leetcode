#include <vector>
using namespace std;

class Solution {
   public:
    vector<int> findEvenNumbers(vector<int>& digits) {
        int n = digits.size();
        vector<int> ans;
        int fre[10]{0};
        for (int i = 0; i < n; i++) {
            fre[digits[i]]++;
        }
        for (int i = 1; i < 10; i++) {
            fre[i]--;
            for (int j = 0; j < 10; j++) {
                fre[j]--;
                for (int k = 0; k < 10; k += 2) {
                    fre[k]--;
                    if (fre[i] >= 0 && fre[j] >= 0 && fre[k] >= 0) {
                        ans.push_back(100 * i + 10 * j + k);
                    }
                    fre[k]++;
                }
                fre[j]++;
            }
            fre[i]++;
        }
        return ans;
    }
};

// [222,228,282,288,822,828,882]
vector<int> digits = {2, 2, 8, 8, 2};

int main() {
    Solution sol;
    vector<int> ans = sol.findEvenNumbers(digits);
    printf("ans = [%d", ans[0]);
    for (int i = 1; i < ans.size(); i++) {
        printf(",%d", ans[i]);
    }
    printf("]\n");
    return 0;
}