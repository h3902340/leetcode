#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class Solution {
   public:
    int numSpecial(vector<vector<int>>& mat) {
        int m = mat.size();
        int n = mat[0].size();
        int res = 0;
        for (int i = 0; i < m; i++) {
            int idx = -1;
            for (int j = 0; j < n; j++) {
                if (mat[i][j] == 1) {
                    if (idx == -1) {
                        idx = j;
                    } else {
                        idx = -1;
                        break;
                    }
                }
            }
            if (idx != -1) {
                int idx2 = -1;
                for (int j = 0; j < m; j++) {
                    if (mat[j][idx] == 1) {
                        if (idx2 == -1) {
                            idx2 = j;
                        } else {
                            idx2 = -1;
                            break;
                        }
                    }
                }
                if (idx2 != -1) {
                    res++;
                }
            }
        }
        return res;
    }
};

int main() {
    string problemName = "1582";
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
        auto res = sol.numSpecial(mat);
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