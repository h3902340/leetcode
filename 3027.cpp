#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class Solution {
   public:
    int numberOfPairs(vector<vector<int>>& points) {
        int n = points.size();
        auto cmp = [](vector<int>& a, vector<int>& b) {
            if (a[0] == b[0]) {
                return a[1] > b[1];
            }
            return a[0] < b[0];
        };
        sort(points.begin(), points.end(), cmp);
        int res = 0;
        for (int i = 0; i < n; i++) {
            int y = INT32_MIN;
            for (int j = i + 1; j < n; j++) {
                if (points[i][1] < points[j][1]) {
                    continue;
                }
                if (y < points[j][1]) {
                    y = points[j][1];
                    res++;
                    if (y == points[i][1]) {
                        break;
                    }
                }
            }
        }
        return res;
    }
};

int main() {
    string problemName = "3027";
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
        auto points = jread_vector2d(line_in);
        auto res = sol.numberOfPairs(points);
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