#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int N = 1e5;
int a[N];
class Solution {
   public:
    int findMaxVal(int n, vector<vector<int>>& restrictions,
                   vector<int>& diff) {
        for (int i = 0; i < n; i++) {
            a[i] = 0;
        }
        int res = 0;
        for (auto& r : restrictions) {
            int idx = r[0];
            int maxVal = r[1];
            a[idx] = maxVal;
        }
        for (int i = 1; i < n; i++) {
            int v = a[i - 1] + diff[i - 1];
            if (a[i] == 0) {
                a[i] = v;
            } else {
                a[i] = min(a[i], v);
            }
        }
        for (int i = n - 1; i >= 1; i--) {
            if (a[i - 1] - a[i] > diff[i - 1]) {
                a[i - 1] = a[i] + diff[i - 1];
            }
            res = max(res, a[i]);
        }
        return res;
    }
};

int main() {
    string problemName = "3796";
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
        auto restrictions = jread_vector2d(line_in);
        getline(file_in, line_in);
        auto diff = jread_vector(line_in);
        auto res = sol.findMaxVal(n, restrictions, diff);
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