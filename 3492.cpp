#include <algorithm>
using namespace std;

class Solution {
   public:
    int maxContainers(int n, int w, int maxWeight) {
        return std::min(maxWeight / w, n * n);
    }
};

int n = 3;
int w = 5;
int maxWeight = 20;

int main() {
    Solution sol;
    int ans = sol.maxContainers(n, w, maxWeight);
    printf("ans = %d\n", ans);  // 4
    return 0;
}