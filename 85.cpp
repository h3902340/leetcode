#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int COLS = 200;
int h[COLS + 1];
int st[COLS + 1];

class Solution {
   public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        int rows = matrix.size();
        int cols = matrix[0].size();
        for (int j = 0; j <= cols; j++) {
            h[j] = 0;
        }
        st[0] = -1;
        int res = 0;
        for (int i = 0; i < rows; i++) {
            int t = 0;
            for (int j = 0; j <= cols; j++) {
                if (j < cols) {
                    if (matrix[i][j] == '1') {
                        h[j]++;
                    } else {
                        h[j] = 0;
                    }
                }
                int d = h[j];
                while (t > 0) {
                    int a = h[st[t]];
                    if (a <= d) {
                        break;
                    }
                    t--;
                    int b = j - st[t] - 1;
                    int c = a * b;
                    res = max(res, c);
                }
                st[++t] = j;
            }
        }
        return res;
    }
};

int main() {
    string problemName = "85";
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
        auto matrix = jread_vector2d_char(line_in);
        auto res = sol.maximalRectangle(matrix);
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