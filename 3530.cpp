#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int NMAX = 22;
struct Data {
    int mask;
    int value;
    int count;
};
vector<int> adj[NMAX];
Data s[1 << NMAX];
int q[NMAX];
int deg[NMAX];
int ancestor[NMAX];
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
            ancestor[i] = 0;
        }
        int cap = 1 << n;
        for (int i = 0; i < cap; i++) {
            memo[i] = 0;
        }
        for (auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            deg[e[1]]++;
            ancestor[e[1]] |= (1 << e[0]);
        }
        int l = 0;
        int r = 0;
        for (int i = 0; i < n; i++) {
            if (deg[i] == 0) {
                Data node;
                node.mask = 1 << i;
                node.value = score[i];
                node.count = 1;
                s[r] = node;
                q[r] = i;
                r++;
            }
        }
        int rold = r;
        while (l < r) {
            int f = q[l++];
            for (auto e : adj[f]) {
                ancestor[e] |= ancestor[f];
                deg[e]--;
                if (deg[e] == 0) {
                    q[r++] = e;
                }
            }
        }
        r = rold;
        while (r > 0) {
            Data f = s[--r];
            for (int i = 0; i < n; i++) {
                int m = 1 << i;
                if (f.mask & m) continue;
                if ((f.mask | ancestor[i]) != f.mask) continue;
                int mask = f.mask | m;
                int count = f.count + 1;
                int value = f.value + score[i] * count;
                if (memo[mask] >= value) continue;
                memo[mask] = value;
                if (mask == cap - 1) continue;
                Data node;
                node.mask = mask;
                node.value = value;
                node.count = count;
                s[r++] = node;
            }
        }
        return memo[cap - 1];
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