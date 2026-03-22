#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class Solution {
   public:
    bool findRotation(vector<vector<int>>& mat, vector<vector<int>>& target) {
        int n = mat.size();
        int same = (1 << 4) - 1;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if ((same & 1) && mat[i][j] != target[i][j]) {
                    same ^= 1;
                }
                if ((same & (1 << 1)) && mat[i][j] != target[j][n - 1 - i]) {
                    same ^= (1 << 1);
                }
                if ((same & (1 << 2)) &&
                    mat[i][j] != target[n - 1 - i][n - 1 - j]) {
                    same ^= (1 << 2);
                }
                if ((same & (1 << 3)) && mat[i][j] != target[n - 1 - j][i]) {
                    same ^= (1 << 3);
                }
                if (!same) {
                    return false;
                }
            }
        }
        return true;
    }
};

int main() {
    string problemName = "1886";
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
        auto target = jread_vector2d(line_in);
        auto res = sol.findRotation(mat, target);
        getline(file_out, line_out);
        auto ans = jread_bool(line_out);
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