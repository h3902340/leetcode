#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int NMAX = 50;
const int KMAX = 10;
int dp[NMAX][KMAX + 1][KMAX + 1];

class Solution {
   public:
    int minTravelTime(int l, int n, int k, vector<int>& position,
                      vector<int>& time) {
        dp[0][0][0] = 0;
        for (int i = 1; i < n; i++) {
            dp[i][0][0] =
                time[i - 1] * (position[i] - position[i - 1]) + dp[i - 1][0][0];
        }
        for (int i = 1; i < n; i++) {
            time[i] += time[i - 1];
        }
        for (int i = 2; i < n; i++) {
            int maxDel = min(i - 1, k);
            for (int j = 1; j <= maxDel; j++) {
                if (i - j < 2) {
                    dp[i][j][j] = time[0] * (position[i] - position[0]);
                    continue;
                }
                for (int x = 0; x <= j; x++) {
                    if (i - j < 3) {
                        dp[i][j][x] =
                            time[0] * (position[i - x - 1] - position[0]) +
                            (time[i - x - 1] - time[0]) *
                                (position[i] - position[i - x - 1]);
                        continue;
                    }
                    int min = INT32_MAX;
                    for (int y = 0; y <= j - x; y++) {
                        int tmp = dp[i - x - 1][j - x][y] +
                                  (time[i - x - 1] - time[i - x - 2 - y]) *
                                      (position[i] - position[i - x - 1]);
                        if (min > tmp) {
                            min = tmp;
                        }
                    }
                    dp[i][j][x] = min;
                }
            }
        }
        int min = INT32_MAX;
        if (n - 1 - k < 2) {
            return dp[n - 1][k][k];
        }
        for (int i = 0; i <= k; i++) {
            if (min > dp[n - 1][k][i]) {
                min = dp[n - 1][k][i];
            }
        }
        return min;
    }
};

int main() {
    string problemName = "3538";
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
        auto l = jread_int(line_in);
        getline(file_in, line_in);
        auto n = jread_int(line_in);
        getline(file_in, line_in);
        auto k = jread_int(line_in);
        getline(file_in, line_in);
        auto position = jread_vector(line_in);
        getline(file_in, line_in);
        auto time = jread_vector(line_in);
        auto res = sol.minTravelTime(l, n, k, position, time);
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
        jprint_int(res, "res");
        jprint_int(ans, "ans");
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