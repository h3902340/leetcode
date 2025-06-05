#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int NMAX = 1e3;
const int CHARMAX = 26;
vector<int> adj[CHARMAX];
int group[CHARMAX];
bool out[CHARMAX];
int s[NMAX];

class Solution {
   public:
    string smallestEquivalentString(string s1, string s2, string baseStr) {
        int n = s1.size();
        int m = baseStr.size();
        for (int i = 0; i < CHARMAX; i++) {
            adj[i].clear();
            group[i] = i;
            out[i] = false;
        }
        for (int i = 0; i < n; i++) {
            int a = s1[i] - 'a';
            int b = s2[i] - 'a';
            adj[a].push_back(b);
            adj[b].push_back(a);
        }
        for (int i = 0; i < CHARMAX; i++) {
            if (out[i]) continue;
            int r = 0;
            s[r++] = i;
            while (r > 0) {
                int t = s[--r];
                group[t] = i;
                out[t] = true;
                for (auto e : adj[t]) {
                    if (out[e]) continue;
                    s[r++] = e;
                }
            }
        }
        string res(m, 0);
        for (int i = 0; i < m; i++) {
            res[i] = group[baseStr[i] - 'a'] + 'a';
        }
        return res;
    }
};

int main() {
    string problemName = "1061";
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
        auto s1 = jread_string(line_in);
        getline(file_in, line_in);
        auto s2 = jread_string(line_in);
        getline(file_in, line_in);
        auto baseStr = jread_string(line_in);
        auto res = sol.smallestEquivalentString(s1, s2, baseStr);
        getline(file_out, line_out);
        auto ans = jread_string(line_out);
        printf("Case %d", ++caseCount);
        if (res == ans) {
            passCount++;
            printf(" %s(PASS)", KGRN);
        } else {
            printf(" %s(WRONG)", KRED);
            allPass = false;
        }
        printf("\n%s", KNRM);
        jprint_string(s1, "s1");
        jprint_string(s2, "s2");
        jprint_string(baseStr, "baseStr");
        jprint_string(res, "res");
        jprint_string(ans, "ans");
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