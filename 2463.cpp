#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define ll long long
const int N = 100;
const int M = 100;
ll dp[N][M];
class Solution {
   public:
    long long minimumTotalDistance(vector<int>& robot,
                                   vector<vector<int>>& factory) {
        int n = robot.size();
        int m = factory.size();
        sort(begin(robot), end(robot));
        sort(begin(factory), end(factory));
        ll b = 0;
        for (int i = 0; i < n; i++) {
            if (i < factory[0][1]) {
                b += abs(factory[0][0] - robot[i]);
                dp[i][0] = b;
            } else {
                dp[i][0] = -1;
            }
            for (int j = 1; j < m; j++) {
                ll a = 0;
                dp[i][j] = -1;
                int cap = min(factory[j][1], i + 1);
                for (int k = 0; k <= cap; k++) {
                    ll pre = i < k ? 0 : dp[i - k][j - 1];
                    if (pre != -1) {
                        if (dp[i][j] == -1) {
                            dp[i][j] = pre + a;
                        } else {
                            dp[i][j] = min(dp[i][j], pre + a);
                        }
                    }
                    if (i >= k) {
                        a += abs(factory[j][0] - robot[i - k]);
                    }
                }
            }
        }
        return dp[n - 1][m - 1];
    }
};

int main() {
    string problemName = "2463";
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
        auto robot = jread_vector(line_in);
        getline(file_in, line_in);
        auto factory = jread_vector2d(line_in);
        auto res = sol.minimumTotalDistance(robot, factory);
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