#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define ll long long
class Solution {
   public:
    long long minimumCost(int cost1, int cost2, int costBoth, int need1,
                          int need2) {
        ll res = 0;
        if (costBoth < cost1 + cost2) {
            if (need1 < need2) {
                res = (ll)need1 * costBoth;
                if (costBoth < cost2) {
                    res += (ll)(need2 - need1) * costBoth;
                } else {
                    res += (ll)(need2 - need1) * cost2;
                }
            } else {
                res = (ll)need2 * costBoth;
                if (costBoth < cost1) {
                    res += (ll)(need1 - need2) * costBoth;
                } else {
                    res += (ll)(need1 - need2) * cost1;
                }
            }
        } else {
            res = (ll)need1 * cost1 + (ll)need2 * cost2;
        }
        return res;
    }
};

int main() {
    string problemName = "3789";
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
        auto cost1 = jread_int(line_in);
        getline(file_in, line_in);
        auto cost2 = jread_int(line_in);
        getline(file_in, line_in);
        auto costBoth = jread_int(line_in);
        getline(file_in, line_in);
        auto need1 = jread_int(line_in);
        getline(file_in, line_in);
        auto need2 = jread_int(line_in);
        auto res = sol.minimumCost(cost1, cost2, costBoth, need1, need2);
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