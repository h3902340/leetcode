#include <vector>
using namespace std;

class Solution {
   public:
    int maxActiveSectionsAfterTrade(string s) {
        vector<int> train;
        char curr = '1';
        int size = 1;
        int oneCount = 0;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '1') {
                oneCount++;
            }
            if (s[i] == curr) {
                size++;
            } else {
                curr = s[i];
                train.push_back(size);
                size = 1;
            }
        }
        if (curr == '0') {
            train.push_back(size);
            train.push_back(1);
        } else {
            train.push_back(size + 1);
        }
        int max = 0;
        for (int i = 1; i < train.size(); i += 2) {
            if (i + 2 >= train.size()) break;
            int sum = train[i] + train[i + 2];
            if (sum > max) {
                max = sum;
            }
        }
        if (train.size() < 5) {
            return oneCount;
        }
        return oneCount + max;
    }
};

string s = "11010110";

int main() {
    Solution sol;
    int ans = sol.maxActiveSectionsAfterTrade(s);
    printf("ans = %d\n", ans);  // 7
    return 0;
}