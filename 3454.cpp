#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define ll long long
struct Data {
    int l;
    int r;
    int y;
    bool isAdd;
};
const int N = 5e4;
const int LEN = N << 1;
Data arr[2][LEN];
const int BIT = 8;
const int TOTAL_BIT = 32;
const int BUCKET_SIZE = 1 << BIT;
const int MASK2 = BUCKET_SIZE - 1;
int buckets[BUCKET_SIZE];
void radixSort(int n) {
    bool p = 0;
    bool q = 1;
    for (int j = 0; j < TOTAL_BIT; j += BIT) {
        for (int i = 0; i < n; i++) {
            buckets[(arr[p][i].y >> j) & MASK2]++;
        }
        for (int i = 1; i < BUCKET_SIZE; i++) {
            buckets[i] += buckets[i - 1];
        }
        for (int i = n - 1; i >= 0; i--) {
            arr[q][--buckets[(arr[p][i].y >> j) & MASK2]] = arr[p][i];
        }
        for (int i = 0; i < BUCKET_SIZE; i++) {
            buckets[i] = 0;
        }
        swap(p, q);
    }
}
int pos[2][LEN];
void radixSort2(int n) {
    bool p = 0;
    bool q = 1;
    for (int j = 0; j < TOTAL_BIT; j += BIT) {
        for (int i = 0; i < n; i++) {
            buckets[(pos[p][i] >> j) & MASK2]++;
        }
        for (int i = 1; i < BUCKET_SIZE; i++) {
            buckets[i] += buckets[i - 1];
        }
        for (int i = n - 1; i >= 0; i--) {
            pos[q][--buckets[(pos[p][i] >> j) & MASK2]] = pos[p][i];
        }
        for (int i = 0; i < BUCKET_SIZE; i++) {
            buckets[i] = 0;
        }
        swap(p, q);
    }
}
struct SegmentTree {
    int l;
    int r;
    int c;
    int v;
};
SegmentTree tree[1 << (32 - __builtin_clz(LEN))];
void init(int i, int l, int r) {
    SegmentTree& node = tree[i];
    node.l = l;
    node.r = r;
    node.c = 0;
    node.v = 0;
    if (node.l + 1 == node.r) return;
    int mid = (l + r) >> 1;
    init(i * 2 + 1, l, mid);
    init(i * 2 + 2, mid, r);
}
void updateParent(int i) {
    if (i == 0) return;
    i = (i - 1) >> 1;
    if (tree[i].c == 0) {
        int a = tree[i * 2 + 1].v;
        int b = tree[i * 2 + 2].v;
        tree[i].v = a + b;
    }
    updateParent(i);
}
void update(int i, int l, int r, bool isAdd) {
    if (tree[i].l == l && tree[i].r == r) {
        if (isAdd) {
            tree[i].c++;
            tree[i].v = pos[0][r] - pos[0][l];
        } else {
            tree[i].c--;
            if (tree[i].c == 0) {
                if (tree[i].l + 1 == tree[i].r) {
                    tree[i].v = 0;
                } else {
                    int a = tree[i * 2 + 1].v;
                    int b = tree[i * 2 + 2].v;
                    tree[i].v = a + b;
                }
            }
        }
        updateParent(i);
        return;
    }
    int mid = (tree[i].l + tree[i].r) >> 1;
    if (r <= mid) {
        update(i * 2 + 1, l, r, isAdd);
    } else if (mid <= l) {
        update(i * 2 + 2, l, r, isAdd);
    } else {
        update(i * 2 + 1, l, mid, isAdd);
        update(i * 2 + 2, mid, r, isAdd);
    }
}

class Solution {
   public:
    double separateSquares(vector<vector<int>>& squares) {
        int n = squares.size();
        int j = 0;
        int k = 0;
        for (int i = 0; i < n; i++) {
            int y = squares[i][1];
            int v = squares[i][2];
            int l = squares[i][0];
            int r = l + v;
            pos[0][k++] = l;
            pos[0][k++] = r;
        }
        radixSort2(k);
        int m = 1;
        for (int i = 1; i < k; i++) {
            if (pos[0][i] != pos[0][i - 1]) {
                pos[0][m++] = pos[0][i];
            }
        }
        unordered_map<int, int> inv;
        for (int i = 0; i < m; i++) {
            inv[pos[0][i]] = i;
        }
        for (int i = 0; i < n; i++) {
            int y = squares[i][1];
            int v = squares[i][2];
            int l = squares[i][0];
            int r = l + v;
            arr[0][j++] = {inv[l], inv[r], y, true};
            arr[0][j++] = {inv[l], inv[r], y + v, false};
        }
        radixSort(j);
        init(0, 0, m - 1);
        update(0, arr[0][0].l, arr[0][0].r, arr[0][0].isAdd);
        int y = arr[0][0].y;
        ll total = 0;
        for (int i = 1; i < j; i++) {
            ll d = (ll)tree[0].v * (arr[0][i].y - y);
            total += d;
            update(0, arr[0][i].l, arr[0][i].r, arr[0][i].isAdd);
            y = arr[0][i].y;
        }
        init(0, 0, m - 1);
        update(0, arr[0][0].l, arr[0][0].r, arr[0][0].isAdd);
        y = arr[0][0].y;
        ll a = 0;
        for (int i = 1; i < j; i++) {
            ll d = (ll)tree[0].v * (arr[0][i].y - y);
            if (((a + d) << 1) >= total) {
                return y + ((double)total / 2 - a) / tree[0].v;
            }
            a += d;
            update(0, arr[0][i].l, arr[0][i].r, arr[0][i].isAdd);
            y = arr[0][i].y;
        }
        return 0;
    }
};

int main() {
    const double TOL = 1e-5;
    string problemName = "3454";
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
        auto squares = jread_vector2d(line_in);
        auto res = sol.separateSquares(squares);
        getline(file_out, line_out);
        auto ans = jread_double(line_out);
        printf("Case %d", ++caseCount);
        if (res - ans < TOL && res - ans > -TOL) {
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