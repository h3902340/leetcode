#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define ll long long
const int N = 12;
const int LEN = 2000;
const int MASK = 1 << N;
int len[MASK];
int med[MASK];
ll dp[MASK];
int temp[2][LEN];
const int BUCKET_SIZE = 256;
const int MASK2 = BUCKET_SIZE - 1;
const int BIAS = 0x80000000;
int buckets[BUCKET_SIZE];
void radixSort(int n) {
    bool p = false;
    for (int i = 0; i < n; i++) {
        temp[p][i] ^= BIAS;
    }
    for (int j = 0; j < 32; j += 8) {
        for (int i = 0; i < n; i++) {
            buckets[(temp[p][i] >> j) & MASK2]++;
        }
        for (int i = 1; i < BUCKET_SIZE; i++) {
            buckets[i] += buckets[i - 1];
        }
        for (int i = n - 1; i >= 0; i--) {
            temp[!p][--buckets[(temp[p][i] >> j) & MASK2]] = temp[p][i];
        }
        for (int i = 0; i < BUCKET_SIZE; i++) {
            buckets[i] = 0;
        }
        p = !p;
    }
    for (int i = 0; i < n; i++) {
        temp[p][i] ^= BIAS;
    }
}

class Solution {
   public:
    long long minMergeCost(vector<vector<int>>& lists) {
        int n = lists.size();
        int cap = 1 << n;
        for (int m = 1; m < cap; m++) {
            if (__builtin_popcount(m) == 1) {
                int i = __builtin_ctz(m);
                int k = lists[i].size();
                len[m] = k;
                med[m] = lists[i][(k - 1) >> 1];
                dp[m] = 0;
                continue;
            }
            int k = 0;
            ll r = 0;
            for (int i = 0; i < n; i++) {
                if (m & (1 << i)) {
                    int l = lists[i].size();
                    for (int j = 0; j < l; j++) {
                        temp[0][k++] = lists[i][j];
                    }
                }
            }
            for (int a = 1; a < m; a++) {
                if ((a | m) != m) {
                    continue;
                }
                int b = m ^ a;
                ll t = dp[a] + dp[b] + len[a] + len[b] + abs(med[a] - med[b]);
                if (r == 0 || r > t) {
                    r = t;
                }
            }
            radixSort(k);
            len[m] = k;
            med[m] = temp[0][(k - 1) >> 1];
            dp[m] = r;
        }
        return dp[cap - 1];
    }
};

int main() {
    string problemName = "3801";
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
        auto lists = jread_vector2d(line_in);
        auto res = sol.minMergeCost(lists);
        getline(file_out, line_out);
        auto ans = jread_longlong(line_out);
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