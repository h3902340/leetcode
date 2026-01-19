#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class Solution {
   public:
    int maxSideLength(vector<vector<int>>& mat, int threshold) {
        int m = mat.size();
        int n = mat[0].size();
        int l = 1;
        int lmax = min(m, n);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (j > 0) {
                    mat[i][j] += mat[i][j - 1];
                }
                if (i > 0) {
                    mat[i][j] += mat[i - 1][j];
                }
                if (i > 0 && j > 0) {
                    mat[i][j] -= mat[i - 1][j - 1];
                }
                if (i < l - 1 || j < l - 1) {
                    continue;
                }
                int cap = min(i + 1, j + 1);
                if (l > cap) {
                    continue;
                }
                for (; l <= cap; l++) {
                    int s = mat[i][j];
                    if (i >= l) {
                        s -= mat[i - l][j];
                    }
                    if (j >= l) {
                        s -= mat[i][j - l];
                    }
                    if (i >= l && j >= l) {
                        s += mat[i - l][j - l];
                    }
                    if (s > threshold) {
                        break;
                    }
                }
                if (l > lmax) {
                    break;
                }
            }
            if (l > lmax) {
                break;
            }
        }
        return l - 1;
    }
};

int main() {
    string problemName = "1292";
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
        auto mat = jread_vector2d(line_in);
        getline(file_in, line_in);
        auto threshold = jread_int(line_in);
        auto res = sol.maxSideLength(mat, threshold);
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