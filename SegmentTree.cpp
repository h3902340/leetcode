#include "Jutil.h"
using namespace std;

#define lg2(x) (33 - __builtin_clz(x))
const int N = 1e5;
class SegmentTree {
    int tree[1 << lg2(N)];
    int _l;
    int _r;

   public:
    void init(int l, int r) {
        _init(1, l, r);
        _l = l;
        _r = r;
    }
    void update(int idx, int v) { _update(idx, v, 1, _l, _r); }
    int query(int x, int y) { return _query(x, y, 1, _l, _r); }

   private:
    void _init(int i, int l, int r) {
        tree[i] = 0;
        if (l == r) {
            return;
        }
        int mid = (l + r) >> 1;
        _init(i * 2, l, mid);
        _init(i * 2 + 1, mid + 1, r);
    }
    void _update(int idx, int v, int i, int l, int r) {
        tree[i] = max(tree[i], v);
        if (l == r) {
            return;
        }
        int mid = (l + r) >> 1;
        if (mid < idx) {
            _update(idx, v, i * 2 + 1, mid + 1, r);
        } else {
            _update(idx, v, i * 2, l, mid);
        }
    }
    int _query(int x, int y, int i, int l, int r) {
        if (x > y) {
            return 0;
        }
        if (l == x && r == y) {
            return tree[i];
        }
        int mid = (l + r) >> 1;
        if (x > mid) {
            return _query(x, y, i * 2 + 1, mid + 1, r);
        }
        if (y <= mid) {
            return _query(x, y, i * 2, l, mid);
        }
        return max(_query(x, mid, i * 2, l, mid),
                   _query(mid + 1, y, i * 2 + 1, mid + 1, r));
    }
};
SegmentTree tree;

int main() {
    vector<int> arr = {1, 3, 5, 7, 4};
    int n = arr.size();
    tree.init(0, n - 1);
    for (int i = 0; i < n; i++) {
        tree.update(i, arr[i]);
    }
    printf("tree.query(1,4): %d\n", tree.query(1, 4));  // tree.query(1,4): 7
}