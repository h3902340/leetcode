#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int D = 9;
const int SUM = 81;
const int P2 = 6;
const int P3 = 4;
const int P5 = 2;
const int P7 = 2;
const int PMAX[4]{P2, P3, P5, P7};
const int prime[4]{2, 3, 5, 7};
int memo[D + 1][SUM + 1][P2 + 1][P3 + 1][P5 + 1][P7 + 1];
int tenPower[D + 1];
int numToFactor[SUM + 1][4];
bool possibleSum[SUM + 1];
bool isInit = false;
static void init() {
    if (isInit) return;
    for (int d = 0; d <= D; d++) {
        for (int sum = 0; sum <= SUM; sum++) {
            for (int p2 = 0; p2 <= P2; p2++) {
                for (int p3 = 0; p3 <= P3; p3++) {
                    for (int p5 = 0; p5 <= P5; p5++) {
                        for (int p7 = 0; p7 <= P7; p7++) {
                            memo[d][sum][p2][p3][p5][p7] = -1;
                        }
                    }
                }
            }
        }
    }
    tenPower[0] = 1;
    for (int i = 1; i <= D; i++) {
        tenPower[i] = tenPower[i - 1] * 10;
    }
    for (int j = 0; j < 4; j++) {
        numToFactor[0][j] = PMAX[j];
    }
    possibleSum[0] = false;
    for (int i = 1; i <= SUM; i++) {
        int a = i;
        for (int j = 0; j < 4; j++) {
            numToFactor[i][j] = 0;
            while (a % prime[j] == 0) {
                numToFactor[i][j]++;
                a /= prime[j];
            }
        }
        if (a == 1) {
            possibleSum[i] = true;
        } else {
            possibleSum[i] = false;
        }
    }
    isInit = true;
}
int digits[D];

class Solution {
   public:
    int beautifulNumbers(int l, int r) {
        init();
        return lower(r) - lower(l) + isBeautiful(l);
    }
    bool isBeautiful(int l) {
        int d = 0;
        int s = 0;
        int prod = 1;
        while (l > 0) {
            int r = l % 10;
            prod *= r;
            s += r;
            l /= 10;
        }
        if (prod % s == 0) {
            return true;
        } else {
            return false;
        }
    }
    int lower(int l) {
        int d = 0;
        int a = l;
        while (a > 0) {
            digits[d++] = a % 10;
            a /= 10;
        }
        int res = 0;
        int p[4]{0};
        int s = 0;
        bool isSkipped = false;
        for (int i = d - 1; i >= 0; i--) {
            int cur = digits[i];
            if (cur == 0) {
                i--;
                int rest = 0;
                while (i >= 0) {
                    rest = rest * 10 + digits[i];
                    i--;
                }
                res += rest + 1;
                isSkipped = true;
                break;
            }
            if (i < d - 1) {
                res += tenPower[i];
            }
            for (int j = 1; j < cur; j++) {
                int snew = s + j;
                int pnew[4];
                for (int k = 0; k < 4; k++) {
                    pnew[k] = p[k] + numToFactor[j][k];
                }
                res += dfs(i, snew, pnew);
            }
            s += cur;
            for (int k = 0; k < 4; k++) {
                p[k] += numToFactor[cur][k];
            }
        }
        if (!isSkipped) {
            res += dfs(0, s, p);
        }
        for (int x = 1; x < d; x++) {
            for (int j = 1; j < 10; j++) {
                int pnew[4];
                for (int k = 0; k < 4; k++) {
                    pnew[k] = numToFactor[j][k];
                }
                res += dfs(d - 1 - x, j, pnew);
            }
        }
        return res;
    }
    int dfs(int d, int s, int p[4]) {
        for (int i = 0; i < 4; i++) {
            if (p[i] > PMAX[i]) {
                p[i] = PMAX[i];
            }
        }
        if (memo[d][s][p[0]][p[1]][p[2]][p[3]] != -1) {
            return memo[d][s][p[0]][p[1]][p[2]][p[3]];
        }
        if (d == 0) {
            if (!possibleSum[s]) {
                memo[d][s][p[0]][p[1]][p[2]][p[3]] = 0;
                return 0;
            }
            for (int j = 0; j < 4; j++) {
                if (numToFactor[s][j] > p[j]) {
                    memo[d][s][p[0]][p[1]][p[2]][p[3]] = 0;
                    return 0;
                }
            }
            memo[d][s][p[0]][p[1]][p[2]][p[3]] = 1;
            return 1;
        }
        int res = tenPower[d - 1];
        for (int i = 1; i < 10; i++) {
            int pnew[4];
            for (int j = 0; j < 4; j++) {
                pnew[j] = p[j] + numToFactor[i][j];
            }
            res += dfs(d - 1, s + i, pnew);
        }
        memo[d][s][p[0]][p[1]][p[2]][p[3]] = res;
        return res;
    }
};

int main() {
    string problemName = "3490";
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
        auto r = jread_int(line_in);
        auto res = sol.beautifulNumbers(l, r);
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
        jprint_int(l, "l");
        jprint_int(r, "r");
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