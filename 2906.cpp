#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define ll long long
const int MOD = 12345;
int mul(int a, int b) { return (ll)a * b % MOD; }
class Solution {
   public:
    vector<vector<int>> constructProductMatrix(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        int pre = 1;
        int suf = 1;
        vector<vector<int>> p(m, vector<int>(n, 1));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                p[i][j] = mul(p[i][j], pre);
                p[m - 1 - i][n - 1 - j] = mul(p[m - 1 - i][n - 1 - j], suf);
                pre = mul(pre, grid[i][j]);
                suf = mul(suf, grid[m - 1 - i][n - 1 - j]);
            }
        }
        return p;
    }
};

int main() {
    string problemName = "2906";
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
        auto res = sol.constructProductMatrix(grid);
        getline(file_out, line_out);
        auto ans = jread_vector2d(line_out);
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