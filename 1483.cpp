#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int N = 5e4;
const int LOGN = 16;
int dp[N][LOGN];

class TreeAncestor {
   public:
    int lgn;
    TreeAncestor(int n, vector<int>& parent) {
        for (int i = 0; i < n; i++) {
            dp[i][0] = parent[i];
        }
        lgn = log2(n) + 1;
        int k = 1;
        for (int j = 1; j < lgn; j++) {
            for (int i = 0; i < n; i++) {
                if (dp[i][j - 1] == -1) {
                    dp[i][j] = -1;
                } else {
                    dp[i][j] = dp[dp[i][j - 1]][j - 1];
                }
            }
            k <<= 1;
        }
    }

    int getKthAncestor(int node, int k) {
        for (int i = lgn - 1; i >= 0; i--) {
            if (k & (1 << i)) {
                node = dp[node][i];
                if (node == -1) break;
            }
        }
        return node;
    }
};

// Case 1
vector<string> cmds = {"TreeAncestor", "getKthAncestor", "getKthAncestor",
                       "getKthAncestor"};
int n = 7;
vector<int> parent = {-1, 0, 0, 1, 1, 2, 2};
vector<vector<int>> queries = {{3, 1}, {5, 2}, {6, 3}};
vector<int> ans = {N, 1, 0, -1};

int main() {
    string problemName = "1483";
    auto begin = jtimer();
    ifstream file_in("testcases/" + problemName + "_in.txt");
    ifstream file_out("testcases/" + problemName + "_out.txt");
    bool allPass = true;
    int caseCount = 0;
    int passCount = 0;
    string line_in;
    string line_out;
    vector<int> res;
    TreeAncestor sol = TreeAncestor(n, parent);
    int j = 0;
    for (int i = 0; i < cmds.size(); i++) {
        if (cmds[i] == "TreeAncestor") {
            res.push_back(N);
        } else if (cmds[i] == "getKthAncestor") {
            res.push_back(sol.getKthAncestor(queries[j][0], queries[j][1]));
            j++;
        }
    }
    printf("Case %d", ++caseCount);
    if (res == ans) {
        passCount++;
        printf(" %s(PASS)", KGRN);
    } else {
        printf(" %s(WRONG)", KRED);
        allPass = false;
    }
    printf("\n%s", KNRM);
    jprint_vector(res, "res");
    jprint_vector(ans, "ans");
    printf("\n");
    if (allPass) {
        printf("%sALL CORRECT [%d/%d]\n%s", KGRN, passCount, caseCount, KNRM);
    } else {
        printf("%sWRONG ANSWER [%d/%d]\n%s", KRED, passCount, caseCount, KNRM);
    }
    auto end = jtimer();
    jprint_time(begin, end);
    return 0;
}