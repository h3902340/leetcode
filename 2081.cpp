#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define ll long long
const int K = 9;
const int N = 30;
ll dp[K + 1][N];
int cnt[K + 1];
bool allFull() {
    for (int i = 2; i <= K; i++) {
        if (cnt[i] < N) {
            return false;
        }
    }
    return true;
}
const int D = 31;
int digits[D];
int tmp[D];
ll digitsToInt(int d) {
    ll n = 0;
    for (int i = 0; i < d; i++) {
        n = n * 10 + digits[i];
    }
    return n;
}
bool isKMirror(int d, int k) {
    ll n = digitsToInt(d);
    d = 0;
    while (n > 0) {
        tmp[d++] = n % k;
        n /= k;
    }
    int i = 0;
    int j = d - 1;
    while (i <= j) {
        if (tmp[i] != tmp[j]) {
            return false;
        }
        i++;
        j--;
    }
    return true;
}

bool isInit = false;
static void init() {
    if (isInit) return;
    for (int i = 2; i <= K; i++) {
        cnt[i] = 0;
    }
    ll i = 1;
    int a = 1;
    ll j = 1;
    bool isAllfull = false;
    while (!isAllfull) {
        ll cap = i * 10;
        while (i < cap) {
            ll n = i;
            int x = a - 1;
            int y = a;
            digits[x] = n % 10;
            n /= 10;
            while (n > 0) {
                int r = n % 10;
                digits[--x] = r;
                digits[y++] = r;
                n /= 10;
            }
            n = digitsToInt(y);
            for (int k = 2; k <= K; k++) {
                if (cnt[k] == N) continue;
                if (isKMirror(y, k)) {
                    dp[k][cnt[k]++] = n;
                }
            }
            isAllfull = allFull();
            if (isAllfull) break;
            i++;
        }
        cap = j * 10;
        while (j < cap) {
            ll n = j;
            int x = a;
            int y = a;
            while (n > 0) {
                int r = n % 10;
                digits[--x] = r;
                digits[y++] = r;
                n /= 10;
            }
            n = digitsToInt(y);
            for (int k = 2; k <= K; k++) {
                if (cnt[k] == N) continue;
                if (isKMirror(y, k)) {
                    dp[k][cnt[k]++] = n;
                }
            }
            isAllfull = allFull();
            if (isAllfull) break;
            j++;
        }
        a++;
    }
    for (int k = 2; k <= K; k++) {
        for (int i = 1; i < N; i++) {
            dp[k][i] += dp[k][i - 1];
        }
    }
    isInit = true;
}

class Solution {
   public:
    long long kMirror(int k, int n) {
        init();
        return dp[k][n - 1];
    }
};

int main() {
    string problemName = "2081";
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
        auto k = jread_int(line_in);
        getline(file_in, line_in);
        auto n = jread_int(line_in);
        auto res = sol.kMirror(k, n);
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