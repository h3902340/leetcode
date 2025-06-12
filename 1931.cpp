#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int MOD = 1e9 + 7;
const int MMAX = 5;
const int NMAX = 1000;
const int TMAX = 1 << (MMAX - 2);
int dp[MMAX + 1][NMAX + 1];
int terms[TMAX][MMAX];
bool isInit = false;
void static init() {
    if (isInit) return;
    for (int i = 0; i < MMAX; i += 2) {
        terms[0][i] = 0;
    }
    for (int i = 1; i < MMAX; i += 2) {
        terms[0][i] = 1;
    }
    for (int i = 1; i < TMAX; i++) {
        for (int j = 0; j < MMAX; j++) {
            terms[i][j] = terms[i - 1][j];
        }
        bool isValid = false;
        while (!isValid) {
            int k = MMAX - 1;
            terms[i][k]++;
            while (terms[i][k] == 3) {
                terms[i][k] = 0;
                k--;
                terms[i][k]++;
            }
            isValid = true;
            for (int j = 1; j < MMAX; j++) {
                if (terms[i][j - 1] == terms[i][j]) {
                    isValid = false;
                    break;
                }
            }
        }
    }
    dp[1][1] = 3;
    for (int i = 2; i <= NMAX; i++) {
        dp[1][i] = (long long)dp[1][i - 1] * 2 % MOD;
    }
    int d = TMAX;
    for (int i = 2; i <= MMAX; i++) {
        int coef[TMAX][TMAX];
        int var[TMAX];
        for (int j = 0; j < TMAX; j += d) {
            for (int k = 0; k < TMAX; k += d) {
                coef[j][k] = 0;
            }
            var[j] = 6;
            int a[i];
            for (int k = 0; k < i; k++) {
                a[k] = 0;
            }
            int kk = 0;
            while (kk < i) {
                bool isValid = true;
                for (int k = 1; k < i; k++) {
                    if (a[k - 1] == a[k]) {
                        isValid = false;
                        break;
                    }
                }
                if (isValid) {
                    for (int k = 0; k < i; k++) {
                        if (terms[j][k] == a[k]) {
                            isValid = false;
                            break;
                        }
                    }
                }
                if (isValid) {
                    for (int jj = 0; jj < TMAX; jj += d) {
                        int a0 = a[0];
                        int a1 = a[1];
                        int a2 = 3 - a0 - a1;
                        int t0 = terms[jj][0];
                        int t1 = terms[jj][1];
                        int t2 = 3 - t0 - t1;
                        bool isBelong = true;
                        for (int k = 2; k < i; k++) {
                            if (a[k] == a0 && terms[jj][k] == t0) {
                                continue;
                            }
                            if (a[k] == a1 && terms[jj][k] == t1) {
                                continue;
                            }
                            if (a[k] == a2 && terms[jj][k] == t2) {
                                continue;
                            }
                            isBelong = false;
                            break;
                        }
                        if (isBelong) {
                            coef[j][jj]++;
                        }
                    }
                }
                a[0]++;
                kk = 0;
                while (a[kk] == 3) {
                    a[kk] = 0;
                    kk++;
                    if (kk == i) break;
                    a[kk]++;
                }
            }
        }
        dp[i][1] = 0;
        for (int k = 0; k < TMAX; k += d) {
            dp[i][1] += var[k];
        }
        int temp[TMAX];
        for (int j = 2; j <= NMAX; j++) {
            for (int k = 0; k < TMAX; k += d) {
                temp[k] = 0;
                for (int kk = 0; kk < TMAX; kk += d) {
                    temp[k] =
                        ((long long)coef[k][kk] * var[kk] + temp[k]) % MOD;
                }
            }
            dp[i][j] = 0;
            for (int k = 0; k < TMAX; k += d) {
                var[k] = temp[k];
                dp[i][j] = (dp[i][j] + var[k]) % MOD;
            }
        }
        d >>= 1;
    }
    isInit = true;
}

class Solution {
   public:
    int colorTheGrid(int m, int n) {
        init();
        return dp[m][n];
    }
};

int main() {
    string problemName = "1931";
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
        auto m = jread_int(line_in);
        getline(file_in, line_in);
        auto n = jread_int(line_in);
        auto res = sol.colorTheGrid(m, n);
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
        jprint(m, "m");
        jprint(n, "n");
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