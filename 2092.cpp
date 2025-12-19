#include <bitset>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int N = 1e5;
int parent[N];
// DSU
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
void unite(int u, int v) {
    int a = find(u);
    int b = find(v);
    if (b != a) {
        if (a == 0) {
            parent[b] = a;
        } else {
            parent[a] = b;
        }
    }
}

class Solution {
   public:
    vector<int> findAllPeople(int n, vector<vector<int>>& meetings,
                              int firstPerson) {
        auto cmp = [](vector<int>& a, vector<int>& b) { return a[2] < b[2]; };
        sort(begin(meetings), end(meetings), cmp);
        for (int i = 0; i < n; i++) {
            parent[i] = -1;
        }
        parent[firstPerson] = 0;
        int m = meetings.size();
        int i = 0;
        int j = 0;
        while (i < m) {
            int t = meetings[i][2];
            while (i < m && meetings[i][2] == t) {
                int a = meetings[i][0];
                int b = meetings[i][1];
                unite(a, b);
                i++;
            }
            for (; j < i; j++) {
                int a = meetings[j][0];
                int b = meetings[j][1];
                if (find(a) != 0) {
                    parent[a] = -1;
                }
                if (find(b) != 0) {
                    parent[b] = -1;
                }
            }
        }
        vector<int> res;
        res.push_back(0);
        for (int i = 1; i < n; i++) {
            if (parent[i] == 0) {
                res.push_back(i);
            }
        }
        return res;
    }
};

int main() {
    string problemName = "2092";
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
        auto meetings = jread_vector2d(line_in);
        getline(file_in, line_in);
        auto firstPerson = jread_int(line_in);
        auto res = sol.findAllPeople(n, meetings, firstPerson);
        getline(file_out, line_out);
        auto ans = jread_vector(line_out);
        printf("Case %d", ++caseCount);
        sort(res.begin(), res.end());
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