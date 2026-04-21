#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int N = 1e5;
class DSU {
    int parent[N];
    int sz[N];

   public:
    void init(int n) {
        for (int i = 0; i < n; i++) {
            parent[i] = -1;
            sz[i] = 1;
        }
    }
    int find(int u) {
        int p = u;
        while (parent[p] != -1) {
            p = parent[p];
        }
        while (parent[u] != -1) {
            int tmp = parent[u];
            parent[u] = p;
            u = tmp;
        }
        return p;
    }
    void unite(int u, int v) {
        int a = find(u);
        int b = find(v);
        if (b != a) {
            if (sz[b] < sz[a]) {
                parent[b] = a;
                sz[a] += sz[b];
            } else {
                parent[a] = b;
                sz[b] += sz[a];
            }
        }
    }
};
DSU dsu;
class Solution {
   public:
    int minimumHammingDistance(vector<int>& source, vector<int>& target,
                               vector<vector<int>>& allowedSwaps) {
        int n = source.size();
        dsu.init(n);
        for (auto& e : allowedSwaps) {
            dsu.unite(e[0], e[1]);
        }
        vector<unordered_map<int, int>> mp(n);
        for (int i = 0; i < n; i++) {
            mp[dsu.find(i)][source[i]]++;
        }
        int match = 0;
        for (int i = 0; i < n; i++) {
            if (mp[dsu.find(i)][target[i]] > 0) {
                mp[dsu.find(i)][target[i]]--;
                match++;
            }
        }
        return n - match;
    }
};

int main() {
    string problemName = "1722";
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
        auto source = jread_vector(line_in);
        getline(file_in, line_in);
        auto target = jread_vector(line_in);
        getline(file_in, line_in);
        auto allowedSwaps = jread_vector2d(line_in);
        auto res = sol.minimumHammingDistance(source, target, allowedSwaps);
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