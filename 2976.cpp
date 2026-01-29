#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define ll long long
const int C = 26;
const int U = 1e9;
int dis[C][C];

class Solution {
   public:
    long long minimumCost(string source, string target, vector<char>& original,
                          vector<char>& changed, vector<int>& cost) {
        int n = source.size();
        int m = original.size();
        for (int i = 0; i < C; i++) {
            for (int j = 0; j < C; j++) {
                if (i == j) {
                    continue;
                }
                dis[i][j] = U;
            }
        }
        for (int i = 0; i < m; i++) {
            int& a = dis[original[i] - 'a'][changed[i] - 'a'];
            if (a > cost[i]) {
                a = cost[i];
            }
        }
        for (int k = 0; k < C; k++) {
            for (int i = 0; i < C; i++) {
                for (int j = 0; j < C; j++) {
                    if (dis[i][j] > dis[i][k] + dis[k][j]) {
                        dis[i][j] = dis[i][k] + dis[k][j];
                    }
                }
            }
        }
        ll res = 0;
        for (int i = 0; i < n; i++) {
            int a = dis[source[i] - 'a'][target[i] - 'a'];
            if (a == U) {
                return -1;
            }
            res += a;
        }
        return res;
    }
};

int main() {
    string problemName = "2976";
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
        auto source = jread_string(line_in);
        getline(file_in, line_in);
        auto target = jread_string(line_in);
        getline(file_in, line_in);
        auto original = jread_vector_char(line_in);
        getline(file_in, line_in);
        auto changed = jread_vector_char(line_in);
        getline(file_in, line_in);
        auto cost = jread_vector(line_in);
        auto res = sol.minimumCost(source, target, original, changed, cost);
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