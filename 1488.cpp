#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const vector<int> EMPTY = {};
const int N = 1e5;
int parent[N + 1];
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
        parent[a] = b;
    }
}
void init(int n) {
    for (int i = 0; i < n; i++) {
        parent[i] = -1;
    }
}

class Solution {
   public:
    vector<int> avoidFlood(vector<int>& rains) {
        int n = rains.size();
        init(n);
        unordered_map<int, int> mp;
        for (int i = 0; i < n; i++) {
            int lake = rains[i];
            if (lake == 0) {
                rains[i] = 1;
                continue;
            }
            rains[i] = -1;
            if (mp.count(lake)) {
                int idx = mp[lake];
                int z = find(idx);
                if (z >= i) {
                    return EMPTY;
                }
                rains[z] = lake;
                unite(z, z + 1);
            }
            mp[lake] = i;
            unite(i, i + 1);
        }
        return rains;
    }
};

int main() {
    string problemName = "1488";
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
        auto rains = jread_vector(line_in);
        auto res = sol.avoidFlood(rains);
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