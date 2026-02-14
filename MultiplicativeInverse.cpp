#include "Jutil.h"
using namespace std;

#define ll long long
const int MOD = 1e9 + 7;
int mul(int a, int b, int p) { return (ll)a * b % p; }
int pow(int a, int b, int p) {
    if (a == 0) return 0;
    if (a == 1) return 1;
    if (b == 0) return 1;
    if (b & 1) {
        int temp = pow(a, b - 1, p);
        return mul(a, temp, p);
    }
    int temp = pow(a, b >> 1, p);
    return mul(temp, temp, p);
}
int inv(int a, int p) { return pow(a, p - 2, p); }

int main() {
    int a = pow(123456789, 3, MOD);
    int b = 123456789;
    int res = mul(a, inv(b, MOD), MOD);
    int ans = pow(123456789, 2, MOD);
    printf("res:%d,ans:%d\n", res, ans);  // res:643499475,ans:643499475
    return 0;
}