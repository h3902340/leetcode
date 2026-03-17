#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

struct Data {
    int h;
    int i;
};
const int N = 1e5;
Data h[2][N];
bool seen[N];
class Solution {
   public:
    int largestSubmatrix(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        int res = 0;
        int p = 0;
        int q = 1;
        int x = 0;
        int y = 0;
        for (int i = 0; i < m; i++) {
            y = 0;
            for (int j = 0; j < x; j++) {
                if (matrix[i][h[p][j].i]) {
                    h[q][y++] = {h[p][j].h + 1, h[p][j].i};
                    seen[h[p][j].i] = true;
                }
            }
            for (int j = 0; j < n; j++) {
                if (!seen[j] && matrix[i][j]) {
                    h[q][y++] = {1, j};
                }
                seen[j] = false;
            }
            int l = 0;
            for (int j = 0; j < y; j++) {
                l = h[q][j].h;
                res = max(res, l * (j + 1));
            }
            swap(p, q);
            swap(x, y);
        }
        return res;
    }
};

int main() {
    string problemName = "1727";
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
        auto matrix = jread_vector2d(line_in);
        auto res = sol.largestSubmatrix(matrix);
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