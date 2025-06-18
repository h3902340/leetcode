#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int N = 1e2;
const int C = 26;
int dp[N][N];
int swapArr[C][C];
class Solution {
   public:
    int minOperations(string word1, string word2) {
        int n = word1.size();
        for (int l = 0; l < n; l++) {
            for (int i = 0; i + l < n; i++) {
                int a = calcOpCount(word1, word2, i, l);
                reverse(word1.begin() + i, word1.begin() + i + l + 1);
                int b = 1 + calcOpCount(word1, word2, i, l);
                reverse(word1.begin() + i, word1.begin() + i + l + 1);
                a = a < b ? a : b;
                for (int j = i; j < i + l; j++) {
                    b = dp[i][j] + dp[j + 1][i + l];
                    a = a < b ? a : b;
                }
                dp[i][i + l] = a;
            }
        }
        return dp[0][n - 1];
    }
    int calcOpCount(string &word1, string &word2, int i, int l) {
        memset(swapArr, 0, sizeof(swapArr));
        int c = 0;
        for (int j = i; j <= i + l; j++) {
            if (word1[j] == word2[j]) continue;
            int x = word1[j] - 'a';
            int y = word2[j] - 'a';
            if (swapArr[y][x] > 0) {
                swapArr[y][x]--;
                c++;
            } else {
                swapArr[x][y]++;
            }
        }
        for (int i = 0; i < C; i++) {
            for (int j = 0; j < C; j++) {
                c += swapArr[i][j];
            }
        }
        return c;
    }
};

int main() {
    string problemName = "3579";
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
        auto word1 = jread_string(line_in);
        getline(file_in, line_in);
        auto word2 = jread_string(line_in);
        auto res = sol.minOperations(word1, word2);
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