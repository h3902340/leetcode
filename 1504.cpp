#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

struct Data {
    int j;
    int h;
    int total;
};
const int N = 150;
const Data NIL = {-1, 0, 0};
Data st[N];

class Solution {
   public:
    int numSubmat(vector<vector<int>>& mat) {
        int m = mat.size();
        int n = mat[0].size();
        int res = 0;
        int c = 0;
        for (int j = 0; j < n; j++) {
            if (mat[0][j] == 0) {
                c = 0;
            } else {
                c++;
                res += c;
            }
        }
        for (int i = 1; i < m; i++) {
            int top = -1;
            for (int j = 0; j < n; j++) {
                if (mat[i][j] == 1) {
                    mat[i][j] += mat[i - 1][j];
                }
                while (top >= 0 && st[top].h > mat[i][j]) {
                    top--;
                }
                Data left = NIL;
                if (top >= 0) {
                    left = st[top];
                }
                int total = (j - left.j) * mat[i][j] + left.total;
                res += total;
                st[++top] = {j, mat[i][j], total};
            }
        }
        return res;
    }
};

int main() {
    string problemName = "1504";
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
        auto res = sol.numSubmat(mat);
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