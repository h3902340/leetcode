#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define ll long long
class Solution {
   public:
    long long minCost(string s, int encCost, int flatCost) {
        int n = s.size();
        return f(s, encCost, flatCost, 0, n);
    }
    ll f(string& s, int encCost, int flatCost, int l, int r) {
        ll a = flatCost;
        int x = 0;
        for (int i = l; i < r; i++) {
            if (s[i] == '1') {
                x++;
            }
        }
        if (x == 0) {
            return a;
        }
        a = (ll)(r - l) * x * encCost;
        if ((r - l) & 1) {
            return a;
        }
        int mid = (l + r) >> 1;
        ll b = f(s, encCost, flatCost, l, mid);
        ll c = f(s, encCost, flatCost, mid, r);
        return min(a, b + c);
    }
};

int main() {
    string problemName = "3864";
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
        auto encCost = jread_int(line_in);
        getline(file_in, line_in);
        auto flatCost = jread_int(line_in);
        auto res = sol.minCost(s, encCost, flatCost);
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