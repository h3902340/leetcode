#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int N = 1e3;
int dp[N][N];

class Solution {
   public:
    int lenLongestFibSubseq(vector<int>& arr) {
        int n = arr.size();
        for (int i = 0; i < n - 1; i++) {
            for (int j = i + 1; j < n; j++) {
                dp[i][j] = 0;
            }
        }
        int res = 0;
        for (int i = 2; i < n; i++) {
            int l = 0;
            int r = i - 1;
            while (l < r) {
                int s = arr[l] + arr[r];
                if (s < arr[i]) {
                    l++;
                } else if (s > arr[i]) {
                    r--;
                } else {
                    dp[r][i] = dp[l][r] + 1;
                    res = max(res, dp[r][i]);
                    l++;
                    r--;
                }
            }
        }
        if (res == 0) {
            return 0;
        }
        return res + 2;
    }
};

int main() {
    string problemName = "873";
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
        auto arr = jread_vector(line_in);
        auto res = sol.lenLongestFibSubseq(arr);
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