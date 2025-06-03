#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int NMAX = 22;
struct Node {
    int mask;
    int value;
    int deg[NMAX];
    int count;
};
vector<int> adj[NMAX];
Node q[1 << NMAX];
int deg[NMAX];
int memo[1 << NMAX];

class Solution {
   public:
    int maxProfit(int n, vector<vector<int>>& edges, vector<int>& score) {
        // switch to Greedy
        if (edges.size() == 0) {
            int res = 0;
            sort(score.begin(), score.end());
            for (int i = 0; i < n; i++) {
                res += (i + 1) * score[i];
            }
            return res;
        }
        if (n == 1) {
            return score[0];
        }
        for (int i = 0; i < n; i++) {
            adj[i].clear();
            deg[i] = 0;
        }
        for (int i = 0; i < (1 << n); i++) {
            memo[i] = 0;
        }
        for (auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            deg[e[1]]++;
        }
        int l = 0;
        int r = 0;
        for (int i = 0; i < n; i++) {
            if (deg[i] == 0) {
                Node node;
                node.mask = 1 << i;
                node.value = score[i];
                node.count = 1;
                for (int i = 0; i < n; i++) {
                    node.deg[i] = deg[i];
                }
                for (auto e : adj[i]) {
                    node.deg[e]--;
                }
                q[r++] = node;
            }
        }
        int allRemoved = (1 << n) - 1;
        while (l < r) {
            Node& f = q[l++];
            for (int i = 0; i < n; i++) {
                int m = 1 << i;
                if (f.mask & m) continue;
                if (f.deg[i] > 0) continue;
                int mask = f.mask | m;
                int value = f.value + score[i] * (f.count + 1);
                if (memo[mask] >= value) continue;
                memo[mask] = value;
                Node node;
                node.mask = mask;
                node.value = value;
                node.count = f.count + 1;
                for (int j = 0; j < n; j++) {
                    node.deg[j] = f.deg[j];
                }
                for (auto e : adj[i]) {
                    node.deg[e]--;
                }
                q[r++] = node;
            }
        }
        return memo[allRemoved];
    }
};

int main() {
    string problemName = "3530";
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
        auto edges = jread_vector2d(line_in);
        getline(file_in, line_in);
        auto score = jread_vector(line_in);
        auto res = sol.maxProfit(n, edges, score);
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