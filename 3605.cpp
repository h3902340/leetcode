#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define lg2(n) (31 - __builtin_clz(n))
const int N = 1e5;
const int LGN = lg2(N) + 1;
int rmq[N][LGN];
int len[N];
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
void init(vector<int>& arr, int n) {
    int lgn = lg2(n);
    for (int i = 0; i < n; i++) {
        rmq[i][0] = arr[i];
    }
    int k = 1;
    for (int l = 1; l <= lgn; l++) {
        int cap = n - (k << 1) + 1;
        for (int i = 0; i < cap; i++) {
            rmq[i][l] = gcd(rmq[i][l - 1], rmq[i + k][l - 1]);
        }
        k <<= 1;
    }
}
int findGCD(int i, int j) {
    int k = lg2(j - i + 1);
    return gcd(rmq[i][k], rmq[j - (1 << k) + 1][k]);
}

class Solution {
   public:
    int minStable(vector<int>& nums, int maxC) {
        int n = nums.size();
        init(nums, n);
        int a = 0;
        int i = 0;
        for (int j = 0; j < n; j++) {
            a = gcd(a, nums[j]);
            while (a == 1) {
                len[i] = j - i;
                i++;
                if (i > j) {
                    a = 0;
                    break;
                }
                a = findGCD(i, j);
            }
        }
        for (int j = i; j < n; j++) {
            len[j] = n - j;
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