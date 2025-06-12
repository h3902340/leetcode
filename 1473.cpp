#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int M = 100;
const int N = 20;
vector<vector<int>> pre(N + 1, vector<int>(M + 1));
vector<vector<int>> cur(N + 1, vector<int>(M + 1));

class Solution {
   public:
    int minCost(vector<int>& houses, vector<vector<int>>& cost, int m, int n,
                int target) {
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= target; j++) {
                pre[i][j] = -1;
            }
        }
        if (houses[0] == 0) {
            for (int j = 0; j < n; j++) {
                pre[j + 1][1] = cost[0][j];
            }
        } else {
            pre[houses[0]][1] = 0;
        }
        for (int i = 1; i < m; i++) {
            if (houses[i] == 0) {
                for (int j = 0; j < n; j++) {
                    for (int k = 1; k <= target; k++) {
                        int a = -1;
                        if (pre[j + 1][k] != -1) {
                            a = pre[j + 1][k] + cost[i][j];
                        }
                        if (k > 1) {
                            for (int j2 = 0; j2 < n; j2++) {
                                if (j == j2) continue;
                                if (pre[j2 + 1][k - 1] == -1) continue;
                                int b = pre[j2 + 1][k - 1] + cost[i][j];
                                if (a == -1 || a > b) {
                                    a = b;
                                }
                            }
                        }
                        cur[j + 1][k] = a;
                    }
                }
            } else {
                for (int j = 0; j < n; j++) {
                    if (j == houses[i] - 1) {
                        for (int k = 1; k <= target; k++) {
                            int a = -1;
                            if (pre[j + 1][k] != -1) {
                                a = pre[j + 1][k];
                            }
                            if (k > 1) {
                                for (int j2 = 0; j2 < n; j2++) {
                                    if (j == j2) continue;
                                    if (pre[j2 + 1][k - 1] == -1) continue;
                                    int b = pre[j2 + 1][k - 1];
                                    if (a == -1 || a > b) {
                                        a = b;
                                    }
                                }
                            }
                            cur[j + 1][k] = a;
                        }
                    } else {
                        for (int k = 1; k <= target; k++) {
                            cur[j + 1][k] = -1;
                        }
                    }
                }
            }
            swap(pre, cur);
        }
        int min = -1;
        for (int j = 1; j <= n; j++) {
            if (pre[j][target] != -1 && (min == -1 || min > pre[j][target])) {
                min = pre[j][target];
            }
        }
        return min;
    }
};

int main() {
    string problemName = "1473";
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
        auto houses = jread_vector(line_in);
        getline(file_in, line_in);
        auto cost = jread_vector2d(line_in);
        getline(file_in, line_in);
        auto m = jread_int(line_in);
        getline(file_in, line_in);
        auto n = jread_int(line_in);
        getline(file_in, line_in);
        auto target = jread_int(line_in);
        auto res = sol.minCost(houses, cost, m, n, target);
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
        jprint_int(res, "res");
        jprint_int(ans, "ans");
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