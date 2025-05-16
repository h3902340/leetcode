#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

// The problem is not clear enough. For conversions = [[0,2,6],[1,2,3]] seems to be a valid testcase, yet many solutions
// do not account for this case. The problem doesn't allow the conversions that are in the opposite directions, but doesn't
// clarify what the "opposite direction" means.
struct Node {
    int node;
    int v;
};
struct Q {
    int node;
    int parent;
};
const int MOD = 1000000007;
const int NMAX = 1e5;
vector<Node> adj[NMAX];
Q q[NMAX];
class Solution {
   public:
    vector<int> baseUnitConversions(vector<vector<int>>& conversions) {
        int n = conversions.size() + 1;
        for (int i = 0; i < n; i++) {
            adj[i].clear();
        }
        vector<int> res(n);
        res[0] = 1;
        for (auto c : conversions) {
            adj[c[0]].push_back({c[1], c[2]});
            adj[c[1]].push_back({c[0], -c[2]});
        }
        int i = 0;
        int j = 1;
        q[0] = {0, -1};
        while (i < j) {
            Q f = q[i++];
            for (auto e : adj[f.node]) {
                if (e.node == f.parent) continue;
                if (e.v > 0) {
                    res[e.node] = (long long)res[f.node] * e.v % MOD;
                } else {
                    res[e.node] = res[f.node] / -e.v;
                }
                q[j++] = {e.node, f.node};
            }
        }
        return res;
    }
};

int main() {
    string problemName = "3528";
    auto begin = jtimer();
    Solution sol;
    ifstream file_in("testcases/" + problemName + "_in.txt");
    ifstream file_out("testcases/" + problemName + "_out.txt");
    bool allPass = true;
    int caseCount = 0;
    int passCount = 0;
    string line_in1;
    string line_out;
    while (getline(file_in, line_in1)) {
        auto conversions = jread_vector2d(line_in1);
        auto res = sol.baseUnitConversions(conversions);
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
        jprint_vector2d_size(conversions, "conversions");
        // printf("grid = %s\n", line_in1.c_str());
        jprint_vector(res, "res");
        jprint_vector(ans, "ans");
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