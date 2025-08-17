#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define ll long long
const int MOD = 1e9 + 7;
const int N = 1e5;
const int K = 316;  // sqrt(N)
int ops[N][K + 1];
int mul(int a, int b) { return (ll)a * b % MOD; }
int pow(int a, int b) {
    if (a == 0) return 0;
    if (a == 1) return 1;
    if (b == 0) return 1;
    if (b & 1) {
        int temp = pow(a, b - 1);
        return mul(a, temp);
    }
    int temp = pow(a, b >> 1);
    return mul(temp, temp);
}
int inv(int a) { return pow(a, MOD - 2); }

// time: O((Q+N)sqrt(N)+Qlog(MOD)), space: O(Nsqrt(N)+log(MOD))
class Solution {
   public:
    int xorAfterQueries(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size();
        int kmax = 0;
        for (auto& q : queries) {
            int k = q[2];
            kmax = max(kmax, k);
        }
        if (mul(kmax, kmax) > n) {
            // O(Qsqrt(N))
            largeK(nums, queries);
        } else {
            // O(Nsqrt(N)+Qlog(MOD))
            smallK(nums, queries, n, kmax);
        }
        int res = 0;
        for (auto e : nums) {
            res ^= e;
        }
        return res;
    }
    void smallK(vector<int>& nums, vector<vector<int>>& queries, int n,
                int kmax) {
        // O(Nsqrt(N))
        for (int i = 0; i < n; i++) {
            for (int j = 1; j <= kmax; j++) {
                ops[i][j] = 1;
            }
        }
        // O(Qlog(MOD))
        for (auto& q : queries) {
            int l = q[0];
            int r = q[1];
            int k = q[2];
            int v = q[3];
            ops[l][k] = mul(ops[l][k], v);
            int r2 = ((r - l) / k + 1) * k + l;
            if (r2 < n) {
                ops[r2][k] = mul(ops[r2][k], inv(v));
            }
        }
        // O(Nsqrt(N))
        for (int i = 0; i < n; i++) {
            for (int k = 1; k <= kmax; k++) {
                int v = ops[i][k];
                if (v == 1) {
                    continue;
                }
                nums[i] = mul(nums[i], v);
                if (i + k < n) {
                    ops[i + k][k] = mul(ops[i + k][k], v);
                }
            }
        }
    }
    void largeK(vector<int>& nums, vector<vector<int>>& queries) {
        for (auto& q : queries) {
            int l = q[0];
            int r = q[1];
            int k = q[2];
            int v = q[3];
            int idx = l;
            // O(sqrt(N))
            while (idx <= r) {
                nums[idx] = mul(nums[idx], v);
                idx += k;
            }
        }
    }
};

int main() {
    string problemName = "3655";
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
        auto queries = jread_vector2d(line_in);
        auto res = sol.xorAfterQueries(nums, queries);
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