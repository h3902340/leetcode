#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define ll long long
class Solution {
   public:
    int minTime(string s, vector<int>& order, int k) {
        int n = s.size();
        int l = 0;
        int r = n - 1;
        int res = n - 1;
        ll all = (ll)n * (n + 1) >> 1;
        if (all < k) {
            return -1;
        }
        if (all == k) {
            return n - 1;
        }
        while (l <= r) {
            int mid = (l + r) >> 1;
            vector<bool> tmp(n, false);
            for (int i = 0; i <= mid; i++) {
                tmp[order[i]] = true;
            }
            ll cnt = all;
            ll a = 0;
            int b = 1;
            for (int i = 0; i < n; i++) {
                if (tmp[i]) {
                    b = 1;
                } else {
                    a += b;
                    b++;
                }
            }
            cnt -= a;
            if (cnt < k) {
                l = mid + 1;
            } else {
                r = mid - 1;
                res = mid;
            }
        }
        return res;
    }
};

int main() {
    string problemName = "3639";
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
        auto s = jread_string(line_in);
        getline(file_in, line_in);
        auto order = jread_vector(line_in);
        getline(file_in, line_in);
        auto k = jread_int(line_in);
        auto res = sol.minTime(s, order, k);
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