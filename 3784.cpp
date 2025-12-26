#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define ll long long
const int C = 26;
ll val[C];
class Solution {
   public:
    long long minCost(string s, vector<int>& cost) {
        int n = s.size();
        ll tot = 0;
        for (int i = 0; i < C; i++) {
            val[i] = 0;
        }
        for (int i = 0; i < n; i++) {
            val[s[i] - 'a'] += cost[i];
            tot += cost[i];
        }
        ll res = 0;
        for (int i = 0; i < C; i++) {
            if (res < val[i]) {
                res = val[i];
            }
        }
        return tot - res;
    }
};

int main() {
    string problemName = "3784";
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
        auto cost = jread_vector(line_in);
        auto res = sol.minCost(s, cost);
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