#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int N = 5e4;
class DSU {
    int parent[N];
    int sz[N];

   public:
    bool parity[N];
    void init(int n) {
        for (int i = 0; i < n; i++) {
            parent[i] = -1;
            sz[i] = 1;
            parity[i] = 0;
        }
    }
    int find(int u) {
        int p = u;
        int pa = 0;
        while (parent[p] != -1) {
            p = parent[p];
            pa ^= parity[p];
        }
        while (parent[u] != -1) {
            int tmp = parent[u];
            parity[u] ^= pa;
            pa ^= parity[tmp];
            parent[u] = p;
            u = tmp;
        }
        return p;
    }
    int unite(int u, int v, int w) {
        int a = find(u);
        int b = find(v);
        if (b != a) {
            if (sz[b] < sz[a]) {
                parent[b] = a;
                sz[a] += sz[b];
                parity[b] = parity[v] ^ parity[u] ^ w;
            } else {
                parent[a] = b;
                sz[b] += sz[a];
                parity[a] = parity[u] ^ parity[v] ^ w;
            }
        } else {
            if ((parity[u] ^ parity[v] ^ w) == 1) {
                return 0;
            }
        }
        return 1;
    }
};
DSU dsu;

class Solution {
   public:
    int numberOfEdgesAdded(int n, vector<vector<int>>& edges) {
        int m = edges.size();

        dsu.init(n);
        int res = 0;
        for (auto& e : edges) {
            int u = e[0];
            int v = e[1];
            int w = e[2];
            res += dsu.unite(u, v, w);
        }
        return res;
    }
};

int main() {
    string problemName = "3887";
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
        auto res = sol.numberOfEdgesAdded(n, edges);
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