#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int N = 40;
const int LGN = 6;
int dp[N][N];
int rmq[N][LGN];
class Solution {
   public:
    int mctFromLeafValues(vector<int>& arr) {
        int n = arr.size();
        int lgn = log2(n);
        for (int i = 0; i < n; i++) {
            dp[i][i] = 0;
            rmq[i][0] = arr[i];
        }
        int k = 1;
        for (int l = 1; l <= lgn; l++) {
            int cap = n - (k << 1) + 1;
            for (int i = 0; i < cap; i++) {
                rmq[i][l] = max(rmq[i][l - 1], rmq[i + k][l - 1]);
            }
            k <<= 1;
        }
        for (int l = 1; l < n; l++) {
            for (int i = 0; i + l < n; i++) {
                int a = INT32_MAX;
                for (int j = i; j < i + l; j++) {
                    int prod = findMax(i, j) * findMax(j + 1, i + l);
                    int b = prod + dp[i][j] + dp[j + 1][i + l];
                    if (a > b) {
                        a = b;
                    }
                }
                dp[i][i + l] = a;
            }
        }
        return dp[0][n - 1];
    }
    int findMax(int i, int j) {
        int k = log2(j - i + 1);
        return max(rmq[i][k], rmq[j - (1 << k) + 1][k]);
    }
};

int main() {
    string problemName = "1130";
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
        auto arr = jread_vector(line_in);
        auto res = sol.mctFromLeafValues(arr);
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