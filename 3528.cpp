#include <vector>
using namespace std;
const int MOD = 1000000007;

// TODO: time is bad (TLE)
class Solution {
   public:
    vector<int> baseUnitConversions(vector<vector<int>> &conversions) {
        int n = conversions.size();
        vector<int> ans(n + 1);
        vector<pair<long long, int>> tree(n + 1, {1, -1});
        for (int i = 0; i < n; i++) {
            tree[conversions[i][0]].second = conversions[i][1];
            int index = conversions[i][0];
            int m = tree[index].first * conversions[i][2] % MOD;
            while (tree[index].second != -1) {
                tree[tree[index].second].first =
                    (tree[tree[index].second].first * m) % MOD;
                index = tree[index].second;
            }
        }
        for (int i = 0; i <= n; i++) {
            ans[i] = tree[i].first;
        }
        return ans;
    }
};