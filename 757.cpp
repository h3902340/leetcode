#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class Solution {
   public:
    int intersectionSizeTwo(vector<vector<int>>& intervals) {
        int n = intervals.size();
        auto cmp = [](vector<int>& a, vector<int>& b) {
            if (a[1] == b[1]) {
                return a[0] > b[0];
            }
            return a[1] < b[1];
        };
        sort(begin(intervals), end(intervals), cmp);
        int res = 2;
        int s = intervals[0][1] - 1;
        int t = intervals[0][1];
        for (int i = 1; i < n; i++) {
            int l = intervals[i][0];
            int r = intervals[i][1];
            if (l <= s) {
                continue;
            }
            if (l > t) {
                res += 2;
                s = r - 1;
                t = r;
            } else {
                res++;
                s = t;
                t = r;
            }
        }
        return res;
    }
};

int main() {
    string problemName = "757";
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
        auto intervals = jread_vector2d(line_in);
        auto res = sol.intersectionSizeTwo(intervals);
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