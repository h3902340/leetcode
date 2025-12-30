#include "Jutil.h"
using namespace std;

int fastPowInternal(int a, int b, int v) {
    if (b == 0) return v;
    if (b & 1) {
        return fastPowInternal(a, b - 1, v * a);
    }
    return fastPowInternal(a * a, b >> 1, v);
}
int fastPow(int a, int b) { return fastPowInternal(a, b, 1); }

int main() {
    int res = fastPow(7, 7);
    printf("res: %d\n", res); // res: 823543
    return 0;
}