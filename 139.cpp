#include <unordered_set>
#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int N = 1000;
int memo[N];
unordered_set<string> se;

class Solution {
   public:
    bool wordBreak(string s, vector<string>& wordDict) {
        se.clear();
        int n = s.size();
        for (int i = 0; i < n; i++) {
            memo[i] = -1;
        }
        for (auto& w : wordDict) {
            se.insert(w);
        }
        return dfs(0, n, s);
    }
    bool dfs(int i, int n, string s) {
        if (i == n) {
            return true;
        }
        if (memo[i] != -1) {
            return memo[i];
        }
        for (int j = 1; i + j <= n; j++) {
            if (se.count(s.substr(i, j))) {
                bool res = dfs(i + j, n, s);
                if (res) {
                    memo[i] = true;
                    return true;
                }
            }
        }
        memo[i] = false;
        return false;
    }
};

int main() {
    string problemName = "139";
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
        auto s = jread_string(line_in);
        getline(file_in, line_in);
        auto wordDict = jread_vector_string(line_in);
        auto res = sol.wordBreak(s, wordDict);
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