#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class Solution {
   public:
    int maximumScore(vector<int>& scores, vector<vector<int>>& edges) {
        int n = scores.size();
        vector<vector<int>> adj(n, vector<int>());
        for (auto& e : edges) {
            int u = e[0];
            int v = e[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        vector<vector<int>> big3(n, vector<int>(3, -1));
        for (int u = 0; u < n; u++) {
            for (auto a : adj[u]) {
                for (int i = 0; i < 3; i++) {
                    if (big3[u][i] == -1 || scores[big3[u][i]] < scores[a]) {
                        for (int j = 2; j > i; j--) {
                            big3[u][j] = big3[u][j - 1];
                        }
                        big3[u][i] = a;
                        break;
                    }
                }
            }
        }
        int res = -1;
        for (auto& e : edges) {
            int u = e[0];
            int v = e[1];
            if (adj[u].size() == 1 || adj[v].size() == 1) {
                continue;
            }
            int s = scores[u] + scores[v];
            int a = 0;
            int b = 0;
            if (big3[u][a] == v) {
                a++;
            }
            if (big3[v][b] == u) {
                b++;
            }
            if (big3[u][a] == big3[v][b]) {
                if (big3[u][a + 1] == v) {
                    if (big3[u][a + 2] != -1) {
                        res = max(res, s + scores[big3[u][a + 2]] +
                                           scores[big3[v][b]]);
                    }
                } else if (big3[u][a + 1] != -1) {
                    res = max(res,
                              s + scores[big3[u][a + 1]] + scores[big3[v][b]]);
                }
                if (big3[v][b + 1] == u) {
                    if (big3[v][b + 2] != -1) {
                        res = max(res, s + scores[big3[u][a]] +
                                           scores[big3[v][b + 2]]);
                    }
                } else if (big3[v][b + 1] != -1) {
                    res = max(res,
                              s + scores[big3[u][a]] + scores[big3[v][b + 1]]);
                }
            } else {
                res = max(res, s + scores[big3[u][a]] + scores[big3[v][b]]);
            }
        }
        return res;
    }
};

int main() {
    string problemName = "2242";
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
        auto scores = jread_vector(line_in);
        getline(file_in, line_in);
        auto edges = jread_vector2d(line_in);
        auto res = sol.maximumScore(scores, edges);
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