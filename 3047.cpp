#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define ll long long
int fmax(int a, int b) { return a > b ? a : b; }
int fmin(int a, int b) { return a > b ? b : a; }
int f(int x1, int x2, int x3, int x4) {
    return x4 - x3 - fmax(x2, x4) + fmin(x1, x3);
}
class Solution {
   public:
    long long largestSquareArea(vector<vector<int>>& bottomLeft,
                                vector<vector<int>>& topRight) {
        int n = bottomLeft.size();
        int mx = 0;
        for (int i = 0; i < n; i++) {
            int a = topRight[i][0] - bottomLeft[i][0];
            int b = topRight[i][1] - bottomLeft[i][1];
            for (int j = i + 1; j < n; j++) {
                int w = a + f(bottomLeft[i][0], topRight[i][0],
                              bottomLeft[j][0], topRight[j][0]);
                if (w <= mx) {
                    continue;
                }
                int h = b + f(bottomLeft[i][1], topRight[i][1],
                              bottomLeft[j][1], topRight[j][1]);
                if (h <= mx) {
                    continue;
                }
                mx = fmin(w, h);
            }
        }
        return (ll)mx * mx;
    }
};

int main() {
    string problemName = "3047";
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
        auto bottomLeft = jread_vector2d(line_in);
        getline(file_in, line_in);
        auto topRight = jread_vector2d(line_in);
        auto res = sol.largestSquareArea(bottomLeft, topRight);
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