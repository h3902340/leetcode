#include "Jutil.h"
using namespace std;

#define lg2(n) (31 - __builtin_clz(n))
const int N = 5e4;
const int LGN = lg2(N) + 1;
int rmq[N][LGN];
void init(vector<int>& arr, int n) {
    int lgn = lg2(n);
    for (int i = 0; i < n; i++) {
        rmq[i][0] = arr[i];
    }
    int k = 1;
    for (int l = 1; l <= lgn; l++) {
        int cap = n - (k << 1) + 1;
        for (int i = 0; i < cap; i++) {
            rmq[i][l] = max(rmq[i][l - 1], rmq[i + k][l - 1]);
        }
        k <<= 1;
    }
}
int findMax(int i, int j) {
    int k = lg2(j - i + 1);
    return max(rmq[i][k], rmq[j - (1 << k) + 1][k]);
}

int main() {
    vector<int> arr = {1, 3, 5, 72, -77, 12};
    int n = arr.size();
    init(arr, n);
    int res = findMax(0, 5);
    printf("res: %d\n", res);  // res: 72
    return 0;
}