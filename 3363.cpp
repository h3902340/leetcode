#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class Solution {
   public:
    int maxCollectedFruits(vector<vector<int>>& fruits) {
        int n = fruits.size();
        int half = n >> 1;
        int res = 0;
        for (int i = 0; i < n; i++) {
            res += fruits[i][i];
        }
        int idx = 0;
        int nxt = 1;
        for (int i = 1; i < half; i++) {
            for (int j = 0; j <= i; j++) {
                int a = 0;
                int b = 0;
                for (int k = j - 1; k <= j + 1; k++) {
                    if (k < 0) {
                        continue;
                    }
                    if (k >= i) {
                        break;
                    }
                    a = max(a, fruits[idx][n - 1 - k]);
                    b = max(b, fruits[n - 1 - k][idx]);
                }
                fruits[nxt][n - 1 - j] += a;
                fruits[n - 1 - j][nxt] += b;
            }
            idx = nxt;
            nxt++;
        }
        if (n & 1) {
            for (int j = 0; j <= half - 1; j++) {
                int a = 0;
                int b = 0;
                for (int k = j - 1; k <= j + 1; k++) {
                    if (k < 0) {
                        continue;
                    }
                    if (k >= half) {
                        break;
                    }
                    a = max(a, fruits[idx][n - 1 - k]);
                    b = max(b, fruits[n - 1 - k][idx]);
                }
                fruits[nxt][n - 1 - j] += a;
                fruits[n - 1 - j][nxt] += b;
            }
            idx = nxt;
            nxt++;
        }
        for (int i = half - 2; i >= 0; i--) {
            for (int j = 0; j <= i; j++) {
                int a = 0;
                int b = 0;
                for (int k = j - 1; k <= j + 1; k++) {
                    if (k < 0) {
                        continue;
                    }
                    if (k > i + 1) {
                        break;
                    }
                    a = max(a, fruits[idx][n - 1 - k]);
                    b = max(b, fruits[n - 1 - k][idx]);
                }
                fruits[nxt][n - 1 - j] += a;
                fruits[n - 1 - j][nxt] += b;
            }
            idx = nxt;
            nxt++;
        }
        res += fruits[n - 2][n - 1];
        res += fruits[n - 1][n - 2];
        return res;
    }
};

int main() {
    string problemName = "3363";
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
        auto fruits = jread_vector2d(line_in);
        auto res = sol.maxCollectedFruits(fruits);
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