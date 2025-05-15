#include <vector>
using namespace std;

class Solution {
   public:
    int maxProduct(int n) {
        int first = 0;
        int second = 0;
        while (n > 0) {
            int d = n % 10;
            n /= 10;
            if (d > first) {
                if (first > second) {
                    second = first;
                }
                first = d;
            } else if (d > second) {
                second = d;
            }
        }
        return first * second;
    }
};

int n = 31;

int main() {
    Solution sol;
    int ans = sol.maxProduct(n);
    printf("ans = %d\n", ans);
    return 0;
}