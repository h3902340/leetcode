#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define ll long long
const int N = 5e4;
int deg[N];

class Solution {
   public:
    long long maximumImportance(int n, vector<vector<int>>& roads) {
        for (int i = 0; i < n; i++) {
            deg[i] = 0;
        }
        for (auto& e : roads) {
            deg[e[0]]++;
            deg[e[1]]++;
        }
        sort(begin(deg), begin(deg) + n);
        ll res = 0;
        for (int i = 0; i < n; i++) {
            res += (ll)deg[i] * (i + 1);
        }
        return res;
    }
};

int main() {
    string problemName = "2285";
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
        auto roads = jread_vector2d(line_in);
        auto res = sol.maximumImportance(n, roads);
        getline(file_out, line_out);
        auto ans = jread_longlong(line_out);
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