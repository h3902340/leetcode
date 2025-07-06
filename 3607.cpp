#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

// DSU
const int C = 1e5;
int parent[C + 1];
set<int> comps[C + 1];

bool isOff[C + 1];

class Solution {
   public:
    vector<int> processQueries(int c, vector<vector<int>>& connections,
                               vector<vector<int>>& queries) {
        for (int i = 1; i <= c; i++) {
            parent[i] = -1;
            isOff[i] = false;
            comps[i].clear();
        }
        for (auto& e : connections) {
            int u = e[0];
            int v = e[1];
            unite(u, v);
        }
        int j = 0;
        for (int i = 1; i <= c; i++) {
            int a = find(i);
            comps[a].insert(i);
        }
        int n = queries.size();
        vector<int> res;
        for (int i = 0; i < n; i++) {
            int type = queries[i][0];
            int node = queries[i][1];
            int a = find(node);
            if (type == 2) {
                comps[a].erase(node);
                isOff[node] = true;
                continue;
            }
            if (!isOff[node]) {
                res.push_back(node);
                continue;
            }
            if (comps[a].empty()) {
                res.push_back(-1);
            } else {
                res.push_back(*comps[a].begin());
            }
        }
        return res;
    }
    // DSU
    void unite(int u, int v) {
        int a = find(u);
        int b = find(v);
        if (b != a) {
            parent[b] = a;
        }
    }
    int find(int u) {
        int p = u;
        while (parent[p] != -1) {
            p = parent[p];
        }
        // collapsing
        while (parent[u] != -1) {
            int tmp = parent[u];
            parent[u] = p;
            u = tmp;
        }
        return p;
    }
};

int main() {
    string problemName = "3607";
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
        auto c = jread_int(line_in);
        getline(file_in, line_in);
        auto connections = jread_vector2d(line_in);
        getline(file_in, line_in);
        auto queries = jread_vector2d(line_in);
        auto res = sol.processQueries(c, connections, queries);
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