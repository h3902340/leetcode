#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int N = 500;
int dp[N][N];
int ll[N][N];
int rr[N][N];

class Solution {
   public:
    int stoneGameV(vector<int>& stoneValue) {
        int n = stoneValue.size();
        dp[0][0] = 0;
        ll[0][0] = stoneValue[0];
        rr[0][0] = stoneValue[0];
        for (int i = 1; i < n; i++) {
            dp[i][i] = 0;
            ll[i][i] = stoneValue[i];
            rr[i][i] = stoneValue[i];
            stoneValue[i] += stoneValue[i - 1];
        }
        for (int j = 1; j < n; j++) {
            for (int i = 0; i + j < n; i++) {
                int tmp = -1;
                int l = 0;
                int r = j - 1;
                int max = -1;
                while (l <= r) {
                    int mid = (l + r) >> 1;
                    int a = stoneValue[i + mid];
                    if (i > 0) {
                        a -= stoneValue[i - 1];
                    }
                    int b = stoneValue[i + j] - stoneValue[i + mid];
                    if (a > b) {
                        r = mid - 1;
                    } else {
                        l = mid + 1;
                        max = mid;
                    }
                }
                if (max != -1) {
                    int a = stoneValue[i + max];
                    if (i > 0) {
                        a -= stoneValue[i - 1];
                    }
                    int b = stoneValue[i + j] - stoneValue[i + max];
                    int c = ll[i][i + max];
                    if (tmp < c) {
                        tmp = c;
                    }
                    if (a == b) {
                        int c2 = rr[i + max + 1][i + j];
                        if (tmp < c2) {
                            tmp = c2;
                        }
                    }
                }
                // break even
                max++;
                if (max < j) {
                    int a = stoneValue[i + max];
                    if (i > 0) {
                        a -= stoneValue[i - 1];
                    }
                    int b = stoneValue[i + j] - stoneValue[i + max];
                    int c = rr[i + max + 1][i + j];
                    if (tmp < c) {
                        tmp = c;
                    }
                    if (a == b) {
                        int c2 = ll[i][i + max];
                        if (tmp < c2) {
                            tmp = c2;
                        }
                    }
                }
                dp[i][i + j] = tmp;
                tmp += stoneValue[i + j];
                if (i > 0) {
                    tmp -= stoneValue[i - 1];
                }
                if (ll[i][i + j - 1] < tmp) {
                    ll[i][i + j] = tmp;
                } else {
                    ll[i][i + j] = ll[i][i + j - 1];
                }
                if (rr[i + 1][i + j] < tmp) {
                    rr[i][i + j] = tmp;
                } else {
                    rr[i][i + j] = rr[i + 1][i + j];
                }
            }
        }
        return dp[0][n - 1];
    }
};

int main() {
    string problemName = "1563";
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
        auto stoneValue = jread_vector(line_in);
        auto res = sol.stoneGameV(stoneValue);
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