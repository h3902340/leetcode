#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

struct Range {
    int l;
    int r;
    int w;
};
const int M = 30;
const int N = 30;
const int DIM = max(M, N);
const Range NIL = {32, -1, 0};
int col[DIM];
int row[DIM];
int dp[DIM][DIM];
int dp2[DIM];

class Solution {
   public:
    int minimumSum(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        int res = INT32_MAX;
        for (int j = 0; j < n; j++) {
            col[j] = 0;
        }
        int colMin = -1;
        int rowMin = -1;
        int colMax = -1;
        int rowMax = -1;
        for (int i = 0; i < m; i++) {
            int v = 0;
            for (int j = 0; j < n; j++) {
                v = (v << 1) + grid[i][j];
                col[j] += (grid[i][j] << i);
            }
            row[i] = v;
            if (v > 0) {
                if (rowMin == -1) {
                    rowMin = i;
                }
                rowMax = i;
            }
        }
        for (int j = 0; j < n; j++) {
            if (col[j] > 0) {
                if (colMin == -1) {
                    colMin = j;
                }
                colMax = j;
            }
        }
        rowMax++;
        colMax++;
        // top to bottom
        for (int i = rowMin; i < rowMax; i++) {
            Range range = NIL;
            int h = 0;
            for (int j = i; j < rowMax; j++) {
                expand(range, row[j]);
                if (range.w > 0) {
                    h++;
                    dp[i][j] = range.w * h;
                } else {
                    if (h > 0) {
                        h++;
                    }
                    dp[i][j] = 0;
                }
            }
        }
        for (int i = rowMin + 1; i < rowMax - 1; i++) {
            for (int j = i + 1; j < rowMax; j++) {
                int a = dp[rowMin][i - 1] + dp[i][j - 1] + dp[j][rowMax - 1];
                res = min(res, a);
            }
        }
        // left to right
        for (int i = colMin; i < colMax; i++) {
            Range range = NIL;
            int h = 0;
            for (int j = i; j < colMax; j++) {
                expand(range, col[j]);
                if (range.w > 0) {
                    h++;
                    dp[i][j] = range.w * h;
                } else {
                    if (h > 0) {
                        h++;
                    }
                    dp[i][j] = 0;
                }
            }
        }
        for (int i = colMin + 1; i < colMax - 1; i++) {
            for (int j = i + 1; j < colMax; j++) {
                int a = dp[colMin][i - 1] + dp[i][j - 1] + dp[j][colMax - 1];
                res = min(res, a);
            }
        }
        if (rowMax - rowMin == 1 || colMax - colMin == 1) {
            return res;
        }
        // top, bottom left, bottom right
        Range range = NIL;
        for (int i = rowMin; i < rowMax - 1; i++) {
            expand(range, row[i]);
            int a = 0;
            if (range.w > 0) {
                a = range.w * (i - rowMin + 1);
            }
            for (int j = colMin; j < colMax - 1; j++) {
                dp2[j] = 0;
            }
            Range rangeLeft = NIL;
            Range rangeRight = NIL;
            int k = colMax - 1;
            int h1 = 0;
            int h2 = 0;
            for (int j = colMin; j < colMax - 1; j++) {
                int b = col[j] >> (i + 1);
                if (b == 0) {
                    if (h1 > 0) {
                        h1++;
                    }
                    if (j > colMin) {
                        dp2[j] += dp2[j - 1];
                    }
                } else {
                    expand(rangeLeft, b);
                    h1++;
                    dp2[j] += rangeLeft.w * h1;
                }
                int c = col[k] >> (i + 1);
                if (c == 0) {
                    if (h2 > 0) {
                        h2++;
                    }
                    if (k < colMax) {
                        dp2[k - 1] += dp2[k];
                    }
                } else {
                    expand(rangeRight, c);
                    h2++;
                    dp2[k - 1] += rangeRight.w * h2;
                }
                k--;
            }
            int b = INT32_MAX;
            for (int j = colMin; j < colMax - 1; j++) {
                b = min(b, dp2[j]);
            }
            res = min(res, a + b);
        }
        // bottom, top left, top right
        range = NIL;
        for (int i = rowMax - 1; i >= rowMin + 1; i--) {
            expand(range, row[i]);
            int a = 0;
            if (range.w > 0) {
                a = range.w * (rowMax - i);
            }
            for (int j = colMin; j < colMax - 1; j++) {
                dp2[j] = 0;
            }
            Range rangeLeft = NIL;
            Range rangeRight = NIL;
            int k = colMax - 1;
            int h1 = 0;
            int h2 = 0;
            for (int j = colMin; j < colMax - 1; j++) {
                int b = col[j] << (32 - i);
                if (b == 0) {
                    if (h1 > 0) {
                        h1++;
                    }
                    if (j > colMin) {
                        dp2[j] += dp2[j - 1];
                    }
                } else {
                    expand(rangeLeft, b);
                    h1++;
                    dp2[j] += rangeLeft.w * h1;
                }
                int c = col[k] << (32 - i);
                if (c == 0) {
                    if (h2 > 0) {
                        h2++;
                    }
                    if (k < colMax) {
                        dp2[k - 1] += dp2[k];
                    }
                } else {
                    expand(rangeRight, c);
                    h2++;
                    dp2[k - 1] += rangeRight.w * h2;
                }
                k--;
            }
            int b = INT32_MAX;
            for (int j = colMin; j < colMax - 1; j++) {
                b = min(b, dp2[j]);
            }
            res = min(res, a + b);
        }
        // left, right top, right bottom
        range = NIL;
        for (int i = colMin; i < colMax - 1; i++) {
            expand(range, col[i]);
            int a = 0;
            if (range.w > 0) {
                a = range.w * (i - colMin + 1);
            }
            for (int j = rowMin; j < rowMax - 1; j++) {
                dp2[j] = 0;
            }
            Range rangeLeft = NIL;
            Range rangeRight = NIL;
            int k = rowMax - 1;
            int h1 = 0;
            int h2 = 0;
            for (int j = rowMin; j < rowMax - 1; j++) {
                int b = row[j] << (33 - n + i);
                if (b == 0) {
                    if (h1 > 0) {
                        h1++;
                    }
                    if (j > rowMin) {
                        dp2[j] += dp2[j - 1];
                    }
                } else {
                    expand(rangeLeft, b);
                    h1++;
                    dp2[j] += rangeLeft.w * h1;
                }
                int c = row[k] << (33 - n + i);
                if (c == 0) {
                    if (h2 > 0) {
                        h2++;
                    }
                    if (k < rowMax) {
                        dp2[k - 1] += dp2[k];
                    }
                } else {
                    expand(rangeRight, c);
                    h2++;
                    dp2[k - 1] += rangeRight.w * h2;
                }
                k--;
            }
            int b = INT32_MAX;
            for (int j = rowMin; j < rowMax - 1; j++) {
                b = min(b, dp2[j]);
            }
            res = min(res, a + b);
        }
        // right, left top, left bottom
        range = NIL;
        for (int i = colMax - 1; i >= colMin + 1; i--) {
            expand(range, col[i]);
            int a = 0;
            if (range.w > 0) {
                a = range.w * (colMax - i);
            }
            for (int j = rowMin; j < rowMax - 1; j++) {
                dp2[j] = 0;
            }
            Range rangeLeft = NIL;
            Range rangeRight = NIL;
            int k = rowMax - 1;
            int h1 = 0;
            int h2 = 0;
            for (int j = rowMin; j < rowMax - 1; j++) {
                int b = row[j] >> (n - i);
                if (b == 0) {
                    if (h1 > 0) {
                        h1++;
                    }
                    if (j > rowMin) {
                        dp2[j] += dp2[j - 1];
                    }
                } else {
                    expand(rangeLeft, b);
                    h1++;
                    dp2[j] += rangeLeft.w * h1;
                }
                int c = row[k] >> (n - i);
                if (c == 0) {
                    if (h2 > 0) {
                        h2++;
                    }
                    if (k < rowMax) {
                        dp2[k - 1] += dp2[k];
                    }
                } else {
                    expand(rangeRight, c);
                    h2++;
                    dp2[k - 1] += rangeRight.w * h2;
                }
                k--;
            }
            int b = INT32_MAX;
            for (int j = rowMin; j < rowMax - 1; j++) {
                b = min(b, dp2[j]);
            }
            res = min(res, a + b);
        }
        return res;
    }
    void expand(Range& range, int v) {
        if (v == 0) {
            return;
        }
        int l = __builtin_clz(v);
        int r = 32 - __builtin_ctz(v);
        range.l = min(range.l, l);
        range.r = max(range.r, r);
        if (range.r > range.l) {
            range.w = range.r - range.l;
        }
    }
};

int main() {
    string problemName = "3197";
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
        auto res = sol.minimumSum(grid);
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