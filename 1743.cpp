#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int N = 1e5;
int deg[N];
int nei[N];
int inv[N];

class Solution {
   public:
    vector<int> restoreArray(vector<vector<int>>& adjacentPairs) {
        int m = adjacentPairs.size();
        int n = m + 1;
        unordered_map<int, int> mp;
        int k = 0;
        for (int i = 0; i < m; i++) {
            int u = adjacentPairs[i][0];
            int v = adjacentPairs[i][1];
            if (!mp.count(u)) {
                mp[u] = k;
                inv[k] = u;
                k++;
            }
            if (!mp.count(v)) {
                mp[v] = k;
                inv[k] = v;
                k++;
            }
            u = mp[u];
            v = mp[v];
            deg[u]++;
            deg[v]++;
            nei[u] ^= v;
            nei[v] ^= u;
        }
        int i = 0;
        for (; i < n; i++) {
            if (deg[i] == 1) {
                break;
            }
        }
        vector<int> res(n);
        for (int j = 0; j < n; j++) {
            res[j] = inv[i];
            int p = nei[i];
            nei[i] = 0;
            nei[p] ^= i;
            i = p;
            deg[j] = 0;
        }
        nei[0] = 0;
        return res;
    }
};

int main() {
    string problemName = "1743";
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
        auto adjacentPairs = jread_vector2d(line_in);
        auto res = sol.restoreArray(adjacentPairs);
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