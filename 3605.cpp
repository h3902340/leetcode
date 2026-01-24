#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int N = 1e5;
const int TREE_SIZE = 1 << (33 - __builtin_clz(N));
struct SegmentTree {
    int l;
    int r;
    int v;
};
int gcd(int a, int b) {
    if (a == 0) {
        return b;
    }
    if (b == 0) {
        return a;
    }
    int atz = __builtin_ctz(a);
    int btz = __builtin_ctz(b);
    int d = min(atz, btz);
    a >>= atz;
    b >>= btz;
    while (a != b) {
        if (a < b) {
            swap(a, b);
        }
        a -= b;
        a >>= __builtin_ctz(a);
    }
    return a <<= d;
}
SegmentTree tree[TREE_SIZE];
int mp[N];
void init(int i, int l, int r) {
    SegmentTree& node = tree[i];
    node.l = l;
    node.r = r;
    node.v = 0;
    if (node.l + 1 == node.r) {
        mp[node.l] = i;
        return;
    }
    int mid = (l + r) >> 1;
    init(i * 2 + 1, l, mid);
    init(i * 2 + 2, mid, r);
}
void updateParent(int i) {
    if (i == 0) return;
    i = (i - 1) >> 1;
    tree[i].v = gcd(tree[i * 2 + 1].v, tree[i * 2 + 2].v);
    updateParent(i);
}
void update(int l, int v) {
    tree[mp[l]].v = v;
    updateParent(mp[l]);
}
int query(int i, int l, int r) {
    if (tree[i].l == l && tree[i].r == r) {
        return tree[i].v;
    }
    int mid = (tree[i].l + tree[i].r) >> 1;
    if (r <= mid) {
        return query(i * 2 + 1, l, r);
    } else if (mid <= l) {
        return query(i * 2 + 2, l, r);
    } else {
        int a = query(i * 2 + 1, l, mid);
        int b = query(i * 2 + 2, mid, r);
        return gcd(a, b);
    }
}
int len[N];

class Solution {
   public:
    int minStable(vector<int>& nums, int maxC) {
        int n = nums.size();
        init(0, 0, n);
        int a = 0;
        int j = 0;
        for (int i = 0; i < n; i++) {
            update(i, nums[i]);
            a = gcd(a, nums[i]);
            while (a == 1) {
                len[j] = i - j;
                j++;
                if (j > i) {
                    a = 0;
                    break;
                }
                a = query(0, j, i + 1);
            }
        }
        for (int i = j; i < n; i++) {
            len[i] = n - i;
        }
        int l = 0;
        int r = n;
        int res = n;
        while (l <= r) {
            int mid = (l + r) >> 1;
            int k = maxC;
            bool ok = true;
            for (int i = 0; i < n - mid; i++) {
                if (len[i] <= mid) {
                    continue;
                }
                if (k == 0) {
                    ok = false;
                    break;
                }
                i += mid;
                k--;
            }
            if (ok) {
                r = mid - 1;
                res = mid;
            } else {
                l = mid + 1;
            }
        }
        return res;
    }
};

int main() {
    string problemName = "3605";
    auto begin = jtimer();
    Solution sol;
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
        auto maxC = jread_int(line_in);
        auto res = sol.minStable(nums, maxC);
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