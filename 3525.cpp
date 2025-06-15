#include <vector>
using namespace std;

// TODO: time is bad (240 ms)
const int KMAX = 5;
struct Data {
    int cnt[KMAX]{0};
    int prod = 1;
};
class Solution {
   public:
    vector<int> resultArray(vector<int> &nums, int k,
                            vector<vector<int>> &queries) {
        int n = nums.size();
        int q = queries.size();
        int d = 1;
        while (n > d) {
            d *= 2;
        }
        vector<Data> tree(d * 2);
        for (int i = 0; i < n; i++) {
            Data &node = tree[i + d];
            int r = nums[i] % k;
            node.cnt[r] = 1;
            node.prod = r;
        }
        for (int i = d - 1; i > 0; i--) {
            Data &p = tree[i];
            Data &l = tree[i * 2];
            Data &r = tree[i * 2 + 1];
            p = mergeNodes(l, r, k);
        }
        vector<int> ans(q, 0);
        for (int i = 0; i < q; i++) {
            int index = queries[i][0] + d;
            Data &c = tree[index];
            int rem = queries[i][1] % k;
            c.prod = rem;
            for (int j = 0; j < k; j++) {
                c.cnt[j] = 0;
            }
            c.cnt[rem] = 1;
            index >>= 1;
            while (index > 0) {
                Data &p = tree[index];
                Data &l = tree[index * 2];
                Data &r = tree[index * 2 + 1];
                p = mergeNodes(l, r, k);
                index >>= 1;
            }
            int l = queries[i][2] + d;
            int r = n - 1 + d;
            Data left;
            Data right;
            while (l <= r) {
                if (l & 1) {
                    left = mergeNodes(left, tree[l++], k);
                }
                if (!(r & 1)) {
                    right = mergeNodes(tree[r--], right, k);
                }
                l >>= 1;
                r >>= 1;
            }
            left = mergeNodes(left, right, k);
            ans[i] = left.cnt[queries[i][3]];
        }
        return ans;
    }

   private:
    Data mergeNodes(Data &l, Data &r, int k) {
        Data p;
        for (int j = 0; j < k; j++) {
            p.cnt[j] = l.cnt[j];
        }
        for (int j = 0; j < k; j++) {
            int rem = l.prod * j % k;
            p.cnt[rem] += r.cnt[j];
        }
        p.prod = l.prod * r.prod % k;
        return p;
    }
};

vector<int> nums = {1, 2, 3, 4, 5};
int k = 3;
vector<vector<int>> queries = {
    {2, 2, 0, 2}, {3, 3, 3, 0}, {0, 1, 0, 1}};  // [2,2,2]

int main() {
    Solution sol;
    vector<int> ans = sol.resultArray(nums, k, queries);
    printf("ans = [%d", ans[0]);
    for (int i = 1; i < ans.size(); i++) {
        printf(",%d", ans[i]);
    }
    printf("]\n");
    return 0;
}