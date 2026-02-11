#include "Jutil.h"
using namespace std;

const int N = 1e5;
const int U = 1e5;
class SparseSet {
    int sparse[U + 1];

   public:
    int dense[N];
    int num;
    void init() { num = 0; }
    bool has(int x) {
        int idx = sparse[x];
        return (idx < num && dense[idx] == x);
    }
    void insert(int x) {
        int idx = sparse[x];
        if (idx >= num || dense[idx] != x) {
            sparse[x] = num;
            dense[num++] = x;
        }
    }
    void remove(int x) {
        int idx = sparse[x];
        if (idx < num && dense[idx] == x) {
            if (idx < num - 1) {
                int other = dense[num - 1];
                sparse[other] = idx;
                dense[idx] = other;
            }
            num--;
        }
    }
};

int main() {
    vector<int> arr = {1, 23, 4, 33, 33, 1};
    int n = arr.size();
    SparseSet se;
    se.init();
    for (int i = 0; i < n; i++) {
        se.insert(arr[i]);
    }
    se.remove(33);
    for (int i = 0; i < se.num; i++) {
        printf("%d,", se.dense[i]);
    }
    printf("\n");  // 1,23,4,
    return 0;
}