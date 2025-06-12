#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int NMAX = 160;
const int BMAX = 160;
int dp[NMAX][2][BMAX + 1];
int temp[NMAX - 1][BMAX + 1];
vector<int> adj[NMAX];
int level[NMAX];

class Solution {
   public:
    int maxProfit(int n, vector<int>& present, vector<int>& future,
                  vector<vector<int>>& hierarchy, int budget) {
        for (int i = 0; i < n; i++) {
            adj[i].clear();
        }
        for (auto& h : hierarchy) {
            adj[h[0] - 1].push_back(h[1] - 1);
        }
        int l = 0;
        int r = 1;
        level[0] = 0;
        while (l < r) {
            int f = level[l++];
            for (auto& e : adj[f]) {
                level[r++] = e;
            }
        }
        for (int i = n - 1; i >= 0; i--) {
            int node = level[i];
            if (adj[node].size() == 0) {
                for (int j = 0; j < present[node]; j++) {
                    dp[node][0][j] = 0;
                }
                int profit = future[node] - present[node];
                if (profit < 0) {
                    profit = 0;
                }
                for (int j = present[node]; j <= budget; j++) {
                    dp[node][0][j] = profit;
                }
                int half = present[node] / 2;
                for (int j = 0; j < half; j++) {
                    dp[node][1][j] = 0;
                }
                profit = future[node] - half;
                if (profit < 0) {
                    profit = 0;
                }
                for (int j = half; j <= budget; j++) {
                    dp[node][1][j] = profit;
                }
            } else {
                // don't buy current node
                for (int j = 0; j <= budget; j++) {
                    temp[0][j] = dp[adj[node][0]][0][j];
                    for (int l = 1; l < adj[node].size(); l++) {
                        int max = 0;
                        for (int k = 0; k <= j; k++) {
                            int tmp =
                                temp[l - 1][k] + dp[adj[node][l]][0][j - k];
                            if (max < tmp) {
                                max = tmp;
                            }
                        }
                        temp[l][j] = max;
                    }
                    dp[node][0][j] = temp[adj[node].size() - 1][j];
                    dp[node][1][j] = temp[adj[node].size() - 1][j];
                }
                // buy current node, but don't buy parent
                int profit = future[node] - present[node];
                for (int j = 0; j <= budget - present[node]; j++) {
                    temp[0][j] = dp[adj[node][0]][1][j];
                    for (int l = 1; l < adj[node].size(); l++) {
                        int max = 0;
                        for (int k = 0; k <= j; k++) {
                            int tmp =
                                temp[l - 1][k] + dp[adj[node][l]][1][j - k];
                            if (max < tmp) {
                                max = tmp;
                            }
                        }
                        temp[l][j] = max;
                    }
                    int total = temp[adj[node].size() - 1][j] + profit;
                    if (dp[node][0][j + present[node]] < total) {
                        dp[node][0][j + present[node]] = total;
                    }
                }
                if (node == 0) {
                    break;
                }
                // buy current node and also buy parent
                int half = present[node] / 2;
                profit = future[node] - half;
                for (int j = 0; j <= budget - half; j++) {
                    temp[0][j] = dp[adj[node][0]][1][j];
                    for (int l = 1; l < adj[node].size(); l++) {
                        int max = 0;
                        for (int k = 0; k <= j; k++) {
                            int tmp =
                                temp[l - 1][k] + dp[adj[node][l]][1][j - k];
                            if (max < tmp) {
                                max = tmp;
                            }
                        }
                        temp[l][j] = max;
                    }
                    int total = temp[adj[node].size() - 1][j] + profit;
                    if (dp[node][1][j + half] < total) {
                        dp[node][1][j + half] = total;
                    }
                }
            }
        }
        return dp[0][0][budget];
    }
};

int main() {
    string problemName = "3562";
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
        auto present = jread_vector(line_in);
        getline(file_in, line_in);
        auto future = jread_vector(line_in);
        getline(file_in, line_in);
        auto hierarchy = jread_vector2d(line_in);
        getline(file_in, line_in);
        auto budget = jread_int(line_in);
        auto res = sol.maxProfit(n, present, future, hierarchy, budget);
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