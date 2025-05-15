#include <unordered_set>
#include <vector>
using namespace std;

class Solution {
   public:
    vector<bool> pathExistenceQueries(int n, vector<int> &nums, int maxDiff,
                                      vector<vector<int>> &queries) {
        vector<int> group(n);
        group[0] = 0;
        for (int i = 1; i < n; i++) {
            if (nums[i] - nums[i - 1] > maxDiff) {
                group[i] = i;
            } else {
                group[i] = group[i - 1];
            }
        }
        int q = queries.size();
        vector<bool> ans(q);
        for (int i = 0; i < q; i++) {
            int l = queries[i][0];
            int r = queries[i][1];
            if (l > r) {
                swap(l, r);
            }
            if (group[r] <= l) {
                ans[i] = true;
            }
        }
        return ans;
    }
};

int n = 4;
vector<int> nums = {2, 5, 6, 8};
int maxDiff = 2;
vector<vector<int>> queries = {{0, 1}, {0, 2}, {1, 3}, {2, 3}};

int main() {
    Solution sol;
    vector<bool> ans = sol.pathExistenceQueries(n, nums, maxDiff, queries);
    printf("ans = [%d", ans[0] == true);
    for (int i = 1; i < ans.size(); i++) {
        printf(",%d", ans[i] == true);
    }
    printf("]\n");
    return 0;
}