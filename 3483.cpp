#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int N = 3;
const int D = 10;
bool memo[D][D][D];

class Solution {
   public:
    int totalNumbers(vector<int>& digits) {
        int res = 0;
        int n = digits.size();
        for (int i = 0; i < D; i++) {
            for (int j = 0; j < D; j++) {
                for (int k = 0; k < D; k++) {
                    memo[i][j][k] = false;
                }
            }
        }
        int dg[N];
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                for (int k = j + 1; k < n; k++) {
                    dg[0] = digits[i];
                    dg[1] = digits[j];
                    dg[2] = digits[k];
                    res += perm(0, dg);
                }
            }
        }
        return res;
    }
    int perm(int i, int digits[N]) {
        if (i == N) {
            if (digits[0] == 0) return 0;
            if (digits[2] & 1) return 0;
            if (memo[digits[0]][digits[1]][digits[2]]) {
                return 0;
            }
            memo[digits[0]][digits[1]][digits[2]] = true;
            return 1;
        }
        int res = 0;
        for (int j = i; j < N; j++) {
            swap(digits[i], digits[j]);
            res += perm(i + 1, digits);
            swap(digits[i], digits[j]);
        }
        return res;
    }
};

int main() {
    string problemName = "3483";
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
        auto digits = jread_vector(line_in);
        auto res = sol.totalNumbers(digits);
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