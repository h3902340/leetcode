#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int DIR = 3;
const int UP_DIR[DIR][2]{{-1, 1}, {0, 1}, {1, 0}};
const int DOWN_DIR[DIR][2]{{1, -1}, {1, 0}, {0, 1}};
class Solution {
   public:
    vector<int> findDiagonalOrder(vector<vector<int>>& mat) {
        int m = mat.size();
        int n = mat[0].size();
        int dim = m * n;
        vector<int> res(dim);
        int i = 0;
        int j = 0;
        bool isDown = false;
        for (int idx = 0; idx < dim; idx++) {
            res[idx] = mat[i][j];
            if (isDown) {
                for (int k = 0; k < DIR; k++) {
                    int x = i + DOWN_DIR[k][0];
                    int y = j + DOWN_DIR[k][1];
                    if (0 <= x && x < m && 0 <= y && y < n) {
                        i = x;
                        j = y;
                        if (k > 0) {
                            isDown = !isDown;
                        }
                        break;
                    }
                }
            } else {
                for (int k = 0; k < DIR; k++) {
                    int x = i + UP_DIR[k][0];
                    int y = j + UP_DIR[k][1];
                    if (0 <= x && x < m && 0 <= y && y < n) {
                        i = x;
                        j = y;
                        if (k > 0) {
                            isDown = !isDown;
                        }
                        break;
                    }
                }
            }
        }
        return res;
    }
};

int main() {
    string problemName = "498";
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
        auto res = sol.findDiagonalOrder(mat);
        getline(file_out, line_out);
        auto ans = jread_vector(line_out);
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