#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int MOD = 1e9 + 7;
const int N = 1000;
const int U = 5000;
vector<int> arr[32];
int dp[2][U];
int add(int a, int b) { return (a + b) % MOD; }
bool isInit = false;
int mx = 0;
void init() {
    for (int i = 0; i <= 5000; i++) {
        int s = 0;
        int t = i;
        while (t > 0) {
            s += t % 10;
            t /= 10;
        }
        arr[s].push_back(i);
    }
    for (int i = 0; i < 32; i++) {
        mx = max(mx, (int)arr[i].size());
    }
}
class Solution {
   public:
    int countArrays(vector<int>& digitSum) {
        if (!isInit) {
            init();
            isInit = true;
        }
        int n = digitSum.size();
        for (int i = 0; i < n; i++) {
            if (digitSum[i] >= 32) {
                return 0;
            }
        }
        dp[0][0] = 1;
        int d = digitSum[0];
        for (int j = 1; j < arr[d].size(); j++) {
            dp[0][j] = 1 + dp[0][j - 1];
        }
        for (int j = arr[d].size(); j < mx; j++) {
            dp[0][j] = dp[0][arr[d].size() - 1];
        }
        int p = 0;
        int q = 1;
        for (int i = 1; i < n; i++) {
            int a = -1;
            for (int j = 0; j < arr[digitSum[i]].size(); j++) {
                int l = a + 1;
                int r = arr[digitSum[i - 1]].size() - 1;
                while (l <= r) {
                    int mid = (l + r) >> 1;
                    if (arr[digitSum[i - 1]][mid] > arr[digitSum[i]][j]) {
                        r = mid - 1;
                    } else {
                        a = mid;
                        l = mid + 1;
                    }
                }
                dp[q][j] = a == -1 ? 0 : dp[p][a];
                if (j > 0) {
                    dp[q][j] = add(dp[q][j], dp[q][j - 1]);
                }
            }
            for (int j = arr[digitSum[i]].size(); j < mx; j++) {
                dp[q][j] = dp[q][arr[digitSum[i]].size() - 1];
            }
            swap(p, q);
        }
        return dp[p][mx - 1];
    }
};

int main() {
    string problemName = "3883";
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
        auto digitSum = jread_vector(line_in);
        auto res = sol.countArrays(digitSum);
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