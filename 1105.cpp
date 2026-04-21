#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int N = 1000;
int dp[N + 1];
class Solution {
   public:
    int minHeightShelves(vector<vector<int>>& books, int shelfWidth) {
        int n = books.size();
        dp[0] = 0;
        for (int i = 1; i <= n; i++) {
            int w = 0;
            int h = 0;
            dp[i] = INT32_MAX;
            for (int j = i; j >= 1; j--) {
                w += books[j - 1][0];
                h = max(h, books[j - 1][1]);
                if (w > shelfWidth) {
                    break;
                }
                dp[i] = min(dp[i], h + dp[j - 1]);
            }
        }
        return dp[n];
    }
};

int main() {
    string problemName = "1105";
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
        auto books = jread_vector2d(line_in);
        getline(file_in, line_in);
        auto shelfWidth = jread_int(line_in);
        auto res = sol.minHeightShelves(books, shelfWidth);
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