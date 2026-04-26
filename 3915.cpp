#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define ll long long
#define lg2(x) (33 - __builtin_clz(x))
const int N = 1e5;
const int U = 1e5;
class SegmentTree {
    ll tree[1 << lg2(U)];

   public:
    void init(int i, int l, int r) {
        tree[i] = 0;
        if (l == r) {
            return;
        }
        int mid = (l + r) >> 1;
        init(i * 2, l, mid);
        init(i * 2 + 1, mid + 1, r);
    }
    void update(int idx, ll v, int i, int l, int r) {
        tree[i] = max(tree[i], v);
        if (l == r) {
            return;
        }
        int mid = (l + r) >> 1;
        if (mid < idx) {
            update(idx, v, i * 2 + 1, mid + 1, r);
        } else {
            update(idx, v, i * 2, l, mid);
        }
    }
    ll query(int x, int y, int i, int l, int r) {
        if (x > y) {
            return 0;
        }
        if (l == x && r == y) {
            return tree[i];
        }
        int mid = (l + r) >> 1;
        if (x > mid) {
            return query(x, y, i * 2 + 1, mid + 1, r);
        }
        if (y <= mid) {
            return query(x, y, i * 2, l, mid);
        }
        return max(query(x, mid, i * 2, l, mid),
                   query(mid + 1, y, i * 2 + 1, mid + 1, r));
    }
};
class Solution {
    SegmentTree up;
    SegmentTree dn;
    ll uptmp[N];
    ll dntmp[N];

   public:
    long long maxAlternatingSum(vector<int>& nums, int k) {
        int n = nums.size();
        int mx = 0;
        for (int i = 0; i < n; i++) {
            mx = max(mx, nums[i]);
        }
        ll res = 0;
        for (int i = 0; i < k; i++) {
            uptmp[i] = nums[i];
            dntmp[i] = nums[i];
            res = max(res, (ll)nums[i]);
        }
        up.init(1, 1, mx);
        dn.init(1, 1, mx);
        for (int i = k; i < n; i++) {
            up.update(nums[i - k], uptmp[i - k], 1, 1, mx);
            dn.update(nums[i - k], dntmp[i - k], 1, 1, mx);
            ll a = dn.query(1, nums[i] - 1, 1, 1, mx);
            ll b = up.query(nums[i] + 1, mx, 1, 1, mx);
            uptmp[i] = a + nums[i];
            dntmp[i] = b + nums[i];
            res = max(res, uptmp[i]);
            res = max(res, dntmp[i]);
        }
        return res;
    }
};

class FenwickTree {
    ll tree[U + 1];
    ll tree2[U + 1];
    int sz;

   public:
    void init(int n) {
        sz = n + 1;
        for (int i = 1; i < sz; i++) {
            tree[i] = 0;
            tree2[i] = 0;
        }
    }
    void updateup(int i, ll v) {
        for (int j = i; j > 0; j -= (j & -j)) {
            tree[j] = max(tree[j], v);
        }
    }
    void updatedn(int i, ll v) {
        for (int j = i; j < sz; j += (j & -j)) {
            tree2[j] = max(tree2[j], v);
        }
    }
    ll queryup(int l) {
        ll s = 0;
        for (int j = l; j < sz; j += (j & -j)) {
            s = max(s, tree[j]);
        }
        return s;
    }
    ll querydn(int r) {
        ll s = 0;
        for (int j = r; j > 0; j -= (j & -j)) {
            s = max(s, tree2[j]);
        }
        return s;
    }
};
class Solution2 {
    FenwickTree t;
    ll uptmp[N];
    ll dntmp[N];

   public:
    long long maxAlternatingSum(vector<int>& nums, int k) {
        int n = nums.size();
        int mx = 0;
        for (int i = 0; i < n; i++) {
            mx = max(mx, nums[i]);
        }
        ll res = 0;
        for (int i = 0; i < k; i++) {
            uptmp[i] = nums[i];
            dntmp[i] = nums[i];
            res = max(res, (ll)nums[i]);
        }
        t.init(mx);
        for (int i = k; i < n; i++) {
            t.updateup(nums[i - k], uptmp[i - k]);
            t.updatedn(nums[i - k], dntmp[i - k]);
            ll a = t.querydn(nums[i] - 1);
            ll b = t.queryup(nums[i] + 1);
            uptmp[i] = a + nums[i];
            dntmp[i] = b + nums[i];
            res = max(res, uptmp[i]);
            res = max(res, dntmp[i]);
        }
        return res;
    }
};

int main() {
    string problemName = "3915";
    auto begin = jtimer();
    Solution2 sol;
    ifstream file_in("testcases/" + problemName + "_in.txt");
    ifstream file_out("testcases/" + problemName + "_out.txt");
    bool allPass = true;
    int caseCount = 0;
    int passCount = 0;
    string line_in;
    string line_out;
    while (getline(file_in, line_in)) {
        auto nums = jread_vector(line_in);
        getline(file_in, line_in);
        auto k = jread_int(line_in);
        auto res = sol.maxAlternatingSum(nums, k);
        getline(file_out, line_out);
        auto ans = jread_int(line_out);
        printf("Case %d", ++caseCount);
        if (res == ans) {
            passCount++;
            printf(" %s(PASS)", KGRN);
        } else {
            printf(" %s(WRONG)", KRED);
            allPass = false;
        }
        printf("\n%s", KNRM);
        jprint(res, "res");
        jprint(ans, "ans");
        printf("\n");
    }
    if (allPass) {
        printf("%sALL CORRECT [%d/%d]\n%s", KGRN, passCount, caseCount, KNRM);
    } else {
        printf("%sWRONG ANSWER [%d/%d]\n%s", KRED, passCount, caseCount, KNRM);
    }
    auto end = jtimer();
    jprint_time(begin, end);
    return 0;
}