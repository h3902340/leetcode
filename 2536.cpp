#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class Solution {
   public:
    vector<vector<int>> rangeAddQueries(int n, vector<vector<int>>& queries) {
        int q = queries.size();
        vector<vector<int>> res(n, vector<int>(n));
        for (int i = 0; i < q; i++) {
            int r1 = queries[i][0];
            int c1 = queries[i][1];
            int r2 = queries[i][2];
            int c2 = queries[i][3];
            res[r1][c1]++;
            if (c2 + 1 < n) {
                res[r1][c2 + 1]--;
            }
            if (r2 + 1 < n) {
                res[r2 + 1][c1]--;
                if (c2 + 1 < n) {
                    res[r2 + 1][c2 + 1]++;
                }
            }
        }
        for (int i = 1; i < n; i++) {
            res[i][0] += res[i - 1][0];
            res[0][i] += res[0][i - 1];
        }
        for (int i = 1; i < n; i++) {
            for (int j = 1; j < n; j++) {
                res[i][j] += res[i - 1][j] + res[i][j - 1] - res[i - 1][j - 1];
            }
        }
        return res;
    }
};

int main() {
    string problemName = "2536";
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
        auto n = jread_int(line_in);
        getline(file_in, line_in);
        auto queries = jread_vector2d(line_in);
        auto res = sol.rangeAddQueries(n, queries);
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