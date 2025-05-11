#include <vector>
using namespace std;

class Solution {
   public:
    bool threeConsecutiveOdds(vector<int>& arr) {
        int n = arr.size();
        int oddCount = 0;
        for (int i = 0; i < n; i++) {
            if (arr[i] & 1) {
                oddCount++;
                if (oddCount == 3) {
                    return true;
                }
            } else {
                oddCount = 0;
            }
        }
        return false;
    }
};

vector<int> arr = {1, 2, 34, 3, 4, 5, 7, 23, 12};

int main() {
    Solution sol;
    bool ans = sol.threeConsecutiveOdds(arr);
    printf("ans = %s\n", ans ? "true" : "false");
    return 0;
}