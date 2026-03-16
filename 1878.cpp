#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int M = 50;
const int N = 50;
int a1[M][N];
int a2[M][N];
int a3[M][N];
int a4[M][N];

class Solution {
   public:
    vector<int> getBiggestThree(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        for (int i = 0; i < m; i++) {
            a1[i][0] = grid[i][0];
            a2[i][n - 1] = grid[i][n - 1];
            a3[i][n - 1] = grid[i][n - 1];
            a4[i][0] = grid[i][0];
        }
        for (int j = 1; j < n; j++) {
            int k = n - 1 - j;
            for (int i = 0; i < m; i++) {
                if (i + 1 < m) {
                    a1[i][j] = a1[i + 1][j - 1] + grid[i][j];
                    a2[i][k] = a2[i + 1][k + 1] + grid[i][k];
                }
                if (i - 1 >= 0) {
                    a3[i][k] = a3[i - 1][k + 1] + grid[i][k];
                    a4[i][j] = a4[i - 1][j - 1] + grid[i][j];
                }
            }
        }
        priority_queue<int> pq;
        int cap = (min(m, n) + 1) >> 1;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                pq.push(grid[i][j]);
            }
        }
        for (int l = 1; l < cap; l++) {
            for (int i = l; i + l < m; i++) {
                for (int j = l; j + l < n; j++) {
                    int a =
                        (a1[i - l][j] - a1[i][j - l]) + a2[i - l + 1][j + 1] +
                        (a3[i + l][j] - a3[i][j + l]) + a4[i + l - 1][j - 1];
                    if (j + l + 1 < n) {
                        a -= a2[i + 1][j + l + 1];
                    }
                    if (j - l - 1 >= 0) {
                        a -= a4[i - 1][j - l - 1];
                    }
                    pq.push(a);
                }
            }
        }
        vector<int> res;
        res.push_back(pq.top());
        pq.pop();
        while (!pq.empty() && res.size() < 3) {
            if (res.back() != pq.top()) {
                res.push_back(pq.top());
            }
            pq.pop();
        }
        return res;
    }
};

int main() {
    string problemName = "1878";
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
        auto res = sol.getBiggestThree(grid);
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