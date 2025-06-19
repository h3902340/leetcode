#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define ll long long
const int N = 5e4;
int q[N];
class Solution {
   public:
    int maximumRobots(vector<int>& chargeTimes, vector<int>& runningCosts,
                      long long budget) {
        int n = chargeTimes.size();
        int i = 0;
        ll c = 0;
        int l = 0;
        int r = -1;
        ll sum = 0;
        for (int j = 0; j < n; j++) {
            while (r >= l && q[r] < chargeTimes[j]) {
                r--;
            }
            q[++r] = chargeTimes[j];
            sum += runningCosts[j];
            c = q[l] + sum * (j - i + 1);
            if (c > budget) {
                if (chargeTimes[i] == q[l]) {
                    l++;
                }
                sum -= runningCosts[i];
                i++;
            }
        }
        return n - i;
    }
};

int main() {
    string problemName = "2398";
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
        auto chargeTimes = jread_vector(line_in);
        getline(file_in, line_in);
        auto runningCosts = jread_vector(line_in);
        getline(file_in, line_in);
        auto budget = jread_longlong(line_in);
        auto res = sol.maximumRobots(chargeTimes, runningCosts, budget);
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