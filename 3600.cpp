#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

struct Data {
    int u;
    int v;
    int s;
};
const int N = 1e5;
int parent[N];

class Solution {
   public:
    int maxStability(int n, vector<vector<int>>& edges, int k) {
        memset(parent, -1, sizeof(parent));
        auto cmp = [&](Data a, Data b) { return a.s < b.s; };
        priority_queue<Data, vector<Data>, decltype(cmp)> pq(cmp);
        int cnt = 0;
        int min = INT32_MAX;
        for (auto& e : edges) {
            int u = e[0];
            int v = e[1];
            int s = e[2];
            int m = e[3];
            if (m) {
                int pu = find(u);
                int pv = find(v);
                if (pu == pv) {
                    return -1;
                }
                parent[pv] = pu;
                if (min > s) {
                    min = s;
                }
                cnt++;
                if (cnt == n) {
                    return -1;
                }
            } else {
                pq.push({u, v, s});
            }
        }
        if (cnt == n - 1) {
            return min;
        }
        while (!pq.empty()) {
            Data t = pq.top();
            pq.pop();
            int pu = find(t.u);
            int pv = find(t.v);
            if (pu == pv) {
                continue;
            }
            parent[pv] = pu;
            if (k >= n - 1 - cnt) {
                t.s <<= 1;
                k--;
            }
            if (min > t.s) {
                min = t.s;
            }
            cnt++;
            if (cnt == n - 1) {
                return min;
            }
        }
        return -1;
    }
    int find(int a) {
        while (parent[a] != -1) {
            a = parent[a];
        }
        return a;
    }
};

int main() {
    string problemName = "3600";
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
        auto k = jread_int(line_in);
        auto res = sol.maxStability(n, edges, k);
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