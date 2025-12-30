#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int N = 1e5;
int deg[N];
int nei[N];
int topo[N];

class Solution {
   public:
    vector<int> maxSubgraphScore(int n, vector<vector<int>>& edges,
                                 vector<int>& good) {
        int m = edges.size();
        for (int i = 0; i < n; i++) {
            if (good[i] == 0) {
                good[i] = -1;
            }
        }
        for (int i = 0; i < m; i++) {
            int u = edges[i][0];
            int v = edges[i][1];
            deg[u]++;
            deg[v]++;
            nei[u] ^= v;
            nei[v] ^= u;
        }
        int j = 0;
        for (int i = 0; i < n; i++) {
            int a = i;
            while (deg[a] == 1) {
                topo[j++] = a;
                int p = nei[a];
                nei[p] ^= a;
                deg[p]--;
                deg[a] = 0;
                if (good[a] > 0) {
                    good[p] += good[a];
                }
                a = p;
            }
        }
        j--;
        for (; j >= 0; j--) {
            int x = topo[j];
            int p = nei[x];
            nei[x] = 0;
            good[x] += max(0, good[p] - max(0, good[x]));
        }
        return good;
    }
};

int main() {
    string problemName = "3772";
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
        auto good = jread_vector(line_in);
        auto res = sol.maxSubgraphScore(n, edges, good);
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