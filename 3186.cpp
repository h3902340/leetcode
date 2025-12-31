#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define ll long long
const int K = 2;
const int BIT = 8;
const int TOTAL_BIT = 32;
const int BUCKET_SIZE = 1 << BIT;
const int MASK = BUCKET_SIZE - 1;
int buckets[BUCKET_SIZE];
void radixSort(vector<int>& nums, int n) {
    vector<int> temp(n);
    for (int j = 0; j < TOTAL_BIT; j += BIT) {
        for (int i = 0; i < n; i++) {
            buckets[(nums[i] >> j) & MASK]++;
        }
        for (int i = 1; i < BUCKET_SIZE; i++) {
            buckets[i] += buckets[i - 1];
        }
        for (int i = n - 1; i >= 0; i--) {
            temp[--buckets[(nums[i] >> j) & MASK]] = nums[i];
        }
        fill(begin(buckets), end(buckets), 0);
        swap(nums, temp);
    }
}
struct Data {
    int num;
    ll sum;
};
Data dp[K + 1];

class Solution {
   public:
    long long maximumTotalDamage(vector<int>& power) {
        int n = power.size();
        for (int i = K; i >= 0; i--) {
            dp[i] = {0, 0};
        }
        radixSort(power, n);
        int a = power[0];
        ll t = a;
        int i = 1;
        for (; i <= n; i++) {
            if (i < n && power[i] == a) {
                t += a;
                continue;
            }
            int upper = a - K;
            for (int j = K; j >= 0; j--) {
                if (dp[j].num < upper) {
                    t += dp[j].sum;
                    break;
                }
            }
            t = max(t, dp[K].sum);
            for (int j = 0; j < K; j++) {
                dp[j] = dp[j + 1];
            }
            dp[K] = {a, t};
            if (i < n) {
                a = power[i];
                t = a;
            }
        }
        return dp[K].sum;
    }
};

int main() {
    string problemName = "3186";
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
        auto power = jread_vector(line_in);
        auto res = sol.maximumTotalDamage(power);
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