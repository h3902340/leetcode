#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int N = 300;
const int C = 26;
const int MAX = C * N;
int dp[2][C];
int dis(int a, int b) { return abs(a % 6 - b % 6) + abs(a / 6 - b / 6); }
class Solution {
   public:
    int minimumDistance(string word) {
        int n = word.size();
        for (int i = 0; i < C; i++) {
            dp[0][i] = 0;
        }
        int p = 0;
        int q = 1;
        for (int k = 1; k < n; k++) {
            int t = word[k] - 'A';
            int u = word[k - 1] - 'A';
            for (int i = 0; i < C; i++) {
                dp[q][i] = MAX;
            }
            for (int i = 0; i < C; i++) {
                dp[q][i] = min(dp[q][i], dp[p][i] + dis(u, t));
                dp[q][u] = min(dp[q][u], dp[p][i] + dis(i, t));
            }
            swap(p, q);
        }
        int res = MAX;
        for (int i = 0; i < C; i++) {
            res = min(res, dp[p][i]);
        }
        return res;
    }
};

int main() {
    string problemName = "1320";
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
        auto word = jread_string(line_in);
        auto res = sol.minimumDistance(word);
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