#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define ll long long
const int MOD = 1e9 + 7;
const int D = 31;
int prefix[D];
int inverse[D];
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

class Solution {
   public:
    vector<int> productQueries(int n, vector<vector<int>>& queries) {
        int i = 0;
        int a = n & -n;
        prefix[i] = a;
        inverse[i] = inv(a);
        i++;
        n ^= a;
        while (n > 0) {
            int a = n & -n;
            prefix[i] = mul(prefix[i - 1], a);
            inverse[i] = inv(prefix[i]);
            i++;
            n ^= a;
        }
        int m = queries.size();
        vector<int> res(m);
        for (int k = 0; k < m; k++) {
            int l = queries[k][0];
            int r = queries[k][1];
            res[k] = prefix[r];
            if (l > 0) {
                res[k] = mul(res[k], inverse[l - 1]);
            }
        }
        return res;
    }
};

int main() {
    string problemName = "2438";
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
        auto n = jread_int(line_in);
        getline(file_in, line_in);
        auto queries = jread_vector2d(line_in);
        auto res = sol.productQueries(n, queries);
        getline(file_out, line_out);
        auto ans = jread_vector(line_out);
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