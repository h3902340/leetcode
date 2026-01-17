#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int N = 1e5;
int deg[N];
int nei[N];
int eIdx[N];
void init(int n) {
    for (int i = 0; i < n; i++) {
        nei[i] = 0;
        eIdx[i] = 0;
    }
}

class Solution {
   public:
    vector<int> minimumFlips(int n, vector<vector<int>>& edges, string start,
                             string target) {
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            if (start[i] == '1') {
                cnt++;
            }
            if (target[i] == '1') {
                cnt--;
            }
        }
        if (cnt & 1) {
            return {-1};
        }
        int m = edges.size();
        init(n);
        for (int i = 0; i < m; i++) {
            int u = edges[i][0];
            int v = edges[i][1];
            deg[u]++;
            deg[v]++;
            nei[u] ^= v;
            nei[v] ^= u;
            eIdx[u] ^= i;
            eIdx[v] ^= i;
        }
        vector<int> res;
        int j = 0;
        for (int i = 0; i < n; i++) {
            int a = i;
            while (deg[a] == 1) {
                int p = nei[a];
                if (start[a] != target[a]) {
                    start[p] = start[p] == '0' ? '1' : '0';
                    res.push_back(eIdx[a]);
                }
                nei[p] ^= a;
                eIdx[p] ^= eIdx[a];
                deg[p]--;
                deg[a] = 0;
                a = p;
            }
        }
        sort(begin(res), end(res));
        return res;
    }
};

int main() {
    string problemName = "3812";
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
        auto start = jread_string(line_in);
        getline(file_in, line_in);
        auto target = jread_string(line_in);
        auto res = sol.minimumFlips(n, edges, start, target);
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