#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int M = 50;
const int N = 50;
int rows[M][N];
int cols[M][N];
int dia1[M][N];
int dia2[M][N];

class Solution {
   public:
    int largestMagicSquare(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                rows[i][j] = grid[i][j];
                if (j > 0) {
                    rows[i][j] += rows[i][j - 1];
                }
                cols[i][j] = grid[i][j];
                if (i > 0) {
                    cols[i][j] += cols[i - 1][j];
                }
                dia1[i][j] = grid[i][j];
                if (i > 0 && j > 0) {
                    dia1[i][j] += dia1[i - 1][j - 1];
                }
                dia2[i][j] = grid[i][j];
                if (i > 0 && j < n - 1) {
                    dia2[i][j] += dia2[i - 1][j + 1];
                }
            }
        }
        int cap = min(m, n);
        for (int l = cap; l > 1; l--) {
            int a = m - l + 1;
            int b = n - l + 1;
            for (int i = 0; i < a; i++) {
                for (int j = 0; j < b; j++) {
                    bool ok = true;
                    int s = rows[i][j + l - 1];
                    if (j > 0) {
                        s -= rows[i][j - 1];
                    }
                    for (int k = 1; k < l; k++) {
                        int t = rows[i + k][j + l - 1];
                        if (j > 0) {
                            t -= rows[i + k][j - 1];
                        }
                        if (s != t) {
                            ok = false;
                            break;
                        }
                        t = cols[i + l - 1][j + k];
                        if (i > 0) {
                            t -= cols[i - 1][j + k];
                        }
                        if (s != t) {
                            ok = false;
                            break;
                        }
                    }
                    if (!ok) {
                        continue;
                    }
                    int t = dia1[i + l - 1][j + l - 1];
                    if (i > 0 && j > 0) {
                        t -= dia1[i - 1][j - 1];
                    }
                    if (s != t) {
                        continue;
                    }
                    t = dia2[i + l - 1][j];
                    if (i > 0 && j + l < n) {
                        t -= dia2[i - 1][j + l];
                    }
                    if (s == t) {
                        return l;
                    }
                }
            }
        }
        return 1;
    }
};

int main() {
    string problemName = "1895";
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
        auto grid = jread_vector2d(line_in);
        auto res = sol.largestMagicSquare(grid);
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