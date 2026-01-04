#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define ll long long
class Solution {
   public:
    long long minimumCost(string s, string t, int flipCost, int swapCost,
                          int crossCost) {
        int n = s.size();
        int a = 0;
        int b = 0;
        for (int i = 0; i < n; i++) {
            if (s[i] != t[i]) {
                a++;
                if (s[i] == '1') {
                    b++;
                } else {
                    b--;
                }
            }
        }
        if (b < 0) {
            b = -b;
        }
        a -= b;
        swapCost = min(swapCost, flipCost << 1);
        crossCost = min(crossCost + swapCost, flipCost << 1);
        b += (a & 1);
        ll res = (ll)(a >> 1) * swapCost + (ll)(b >> 1) * crossCost;
        if (b & 1) {
            res += flipCost;
        }
        return res;
    }
};

int main() {
    string problemName = "3800";
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
        auto t = jread_string(line_in);
        getline(file_in, line_in);
        auto flipCost = jread_int(line_in);
        getline(file_in, line_in);
        auto swapCost = jread_int(line_in);
        getline(file_in, line_in);
        auto crossCost = jread_int(line_in);
        auto res = sol.minimumCost(s, t, flipCost, swapCost, crossCost);
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