#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define ll long long
const int N = 1e5;
ll dp[2][N];
ll pre[N];
ll suf[N];
class Solution {
   public:
    long long maxPoints(vector<vector<int>>& points) {
        int m = points.size();
        int n = points[0].size();
        for (int j = 0; j < n; j++) {
            dp[0][j] = points[0][j];
        }
        int p = 0;
        int q = 1;
        for (int i = 1; i < m; i++) {
            for (int j = 0; j < n; j++) {
                pre[j] = dp[p][j] - (n - 1 - j);
                suf[j] = dp[p][j] - j;
            }
            for (int j = 1; j < n; j++) {
                pre[j] = max(pre[j], pre[j - 1]);
                suf[n - 1 - j] = max(suf[n - 1 - j], suf[n - j]);
            }
            for (int j = 0; j < n; j++) {
                dp[q][j] = points[i][j] + max(pre[j] + (n - 1 - j), suf[j] + j);
            }
            swap(p, q);
        }
        ll res = 0;
        for (int j = 0; j < n; j++) {
            res = max(res, dp[p][j]);
        }
        return res;
    }
};

int main() {
    string problemName = "1937";
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
        auto res = sol.maxPoints(points);
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