#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define ll long long
const int MOD = 1e9 + 7;
class Solution {
   public:
    int kConcatenationMaxSum(vector<int>& arr, int k) {
        int n = arr.size();
        ll a = 0;
        ll b = 0;
        ll s = 0;
        for (int i = 0; i < n; i++) {
            b = max(b + arr[i], (ll)arr[i]);
            a = max(a, b);
            s += arr[i];
        }
        if (k == 1) {
            return a;
        }
        for (int i = 0; i < n; i++) {
            b = max(b + arr[i], (ll)arr[i]);
            a = max(a, b);
        }
        if (s > 0) {
            return (a + s * (k - 2)) % MOD;
        }
        return a % MOD;
    }
};

int main() {
    string problemName = "1191";
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
        auto arr = jread_vector(line_in);
        getline(file_in, line_in);
        auto k = jread_int(line_in);
        auto res = sol.kConcatenationMaxSum(arr, k);
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