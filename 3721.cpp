#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define lg2(x) (33 - __builtin_clz(x))
const int N = 1e5;
const int U = 1e5;
const int SZ = 1 << lg2(N);
class SegmentTree {
    struct Node {
        int mn;
        int mx;
        int v;
    };
    Node tree[SZ];
    int n;

   public:
    void init(int _n) {
        n = _n;
        int sz = 1 << lg2(n);
        for (int i = 0; i < sz; i++) {
            tree[i] = {0, 0, 0};
        }
    }
    void pull(int i) {
        while (i > 0) {
            int p = (i - 1) >> 1;
            int a = p * 2 + 1;
            int b = a + 1;
            tree[p].mn = tree[p].v + min(tree[a].mn, tree[b].mn);
            tree[p].mx = tree[p].v + max(tree[a].mx, tree[b].mx);
            i = p;
        }
    }
    void update(int l, int r, int v) {
        int i = 0;
        int tl = 0;
        int tr = n;
        int mid = (tl + tr) >> 1;
        while (true) {
            if (mid < l) {
                i = i * 2 + 2;
                tl = mid;
            } else if (mid - 1 > r) {
                i = i * 2 + 1;
                tr = mid;
            } else {
                break;
            }
            mid = (tl + tr) >> 1;
        }
        if (tl + 1 == tr) {
            tree[i].mn += v;
            tree[i].mx += v;
            tree[i].v += v;
            pull(i);
            return;
        }
        int a = i * 2 + 1;
        int atr = mid;
        while (l < atr) {
            int pretl = tl;
            while (tl < l) {
                a = a * 2 + 2;
                pretl = tl;
                tl = (tl + atr) >> 1;
            }
            tree[a].mn += v;
            tree[a].mx += v;
            tree[a].v += v;
            a--;
            atr = tl;
            tl = pretl;
        }
        pull(a + 1);
        a = i * 2 + 2;
        int atl = mid;
        while (atl <= r) {
            int pretr = tr;
            while (r < tr - 1) {
                a = a * 2 + 1;
                pretr = tr;
                tr = (atl + tr) >> 1;
            }
            tree[a].mn += v;
            tree[a].mx += v;
            tree[a].v += v;
            a++;
            atl = tr;
            tr = pretr;
        }
        pull(a - 1);
    }
    int query(int r) {
        int i = 0;
        int tl = 0;
        int tr = n;
        int v = 0;
        bool found = false;
        while (tl <= r) {
            int pretr = tr;
            while (tr - 1 > r) {
                v += tree[i].v;
                i = i * 2 + 1;
                pretr = tr;
                tr = (tl + tr) >> 1;
            }
            if (tree[i].mn + v <= 0 && tree[i].mx + v >= 0) {
                found = true;
                break;
            }
            if (i == 0) {
                break;
            }
            i++;
            tl = tr;
            tr = pretr;
        }
        if (found) {
            while (tl + 1 < tr) {
                v += tree[i].v;
                int a = i * 2 + 1;
                int b = a + 1;
                int mid = (tl + tr) >> 1;
                if (tree[a].mn + v <= 0 && tree[a].mx + v >= 0) {
                    tr = mid;
                    i = a;
                } else {
                    tl = mid;
                    i = b;
                }
            }
            return tl;
        }
        return -1;
    }
};
int rightMost[U + 1];
SegmentTree tree;

class Solution {
   public:
    int longestBalanced(vector<int>& nums) {
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            rightMost[nums[i]] = -1;
        }
        tree.init(n);
        int res = 0;
        for (int i = 0; i < n; i++) {
            int r = rightMost[nums[i]];
            rightMost[nums[i]] = i;
            if (nums[i] & 1) {
                tree.update(r + 1, i, 1);
            } else {
                tree.update(r + 1, i, -1);
            }
            int l = tree.query(i);
            if (l != -1) {
                int a = i + 1 - l;
                if (res < a) {
                    res = a;
                }
            }
        }
        return res;
    }
};

int main() {
    string problemName = "3721";
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
        auto res = sol.longestBalanced(nums);
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