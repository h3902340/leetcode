#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class Solution {
   public:
    int shipWithinDays(vector<int>& weights, int days) {
        int n = weights.size();
        int l = 0;
        int r = 0;
        for (auto w : weights) {
            if (l < w) {
                l = w;
            }
            r += w;
        }
        int res = r;
        while (l <= r) {
            int mid = (l + r) >> 1;
            int c = 0;
            int i = 0;
            while (i < n) {
                int load = 0;
                while (i < n && load < mid) {
                    load += weights[i++];
                }
                if (load > mid) {
                    load -= weights[--i];
                }
                c++;
            }
            if (c > days) {
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
    string problemName = "1011";
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
        auto weights = jread_vector(line_in);
        getline(file_in, line_in);
        auto days = jread_int(line_in);
        auto res = sol.shipWithinDays(weights, days);
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