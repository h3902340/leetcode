#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

struct Node {
    int num;
    int index;
    int pos;
    int rem;
    int mask;
};
const int KMAX = 100;
const int NMAX = 13;
const int DMAX = 79;
Node s[1 << NMAX];
bool memo[1 << NMAX][KMAX];
int dp[DMAX];
int digit[NMAX];

class Solution {
   public:
    vector<int> concatenatedDivisibility(vector<int>& nums, int k) {
        int n = nums.size();
        dp[0] = 1;
        for (int i = 1; i < DMAX; i++) {
            dp[i] = (dp[i - 1] * 10) % k;
        }
        sort(nums.begin(), nums.end());
        for (int i = 0; i < (1 << n); i++) {
            for (int j = 0; j < k; j++) {
                memo[i][j] = false;
            }
        }
        int digitTotal = 0;
        for (int i = 0; i < n; i++) {
            digit[i] = countDigit(nums[i]);
            digitTotal += digit[i];
        }
        vector<int> ans(n);
        int t = -1;
        const int allUsed = (1 << n) - 1;
        for (int i = n - 1; i >= 0; i--) {
            int pos = digitTotal - digit[i];
            t++;
            s[t].num = nums[i];
            s[t].index = 0;
            s[t].pos = pos;
            s[t].rem = (nums[i] * dp[pos]) % k;
            s[t].mask = 1 << i;
        }
        while (t >= 0) {
            Node top = s[t--];
            ans[top.index] = top.num;
            if (top.mask == allUsed) {
                if (top.rem == 0) {
                    return ans;
                }
                continue;
            }
            if (memo[top.mask][top.rem]) {
                continue;
            }
            memo[top.mask][top.rem] = true;
            for (int i = n - 1; i >= 0; i--) {
                int m = 1 << i;
                if (top.mask & m) {
                    continue;
                }
                int pos = top.pos - digit[i];
                t++;
                s[t].num = nums[i];
                s[t].index = top.index + 1;
                s[t].pos = pos;
                s[t].rem = (top.rem + nums[i] * dp[pos]) % k;
                s[t].mask = top.mask | m;
            }
        }
        return {};
    }

   private:
    int countDigit(int num) {
        int d = 0;
        int m = 1;
        while (m <= num) {
            m *= 10;
            d++;
        }
        return d;
    }
};

int main() {
    string problemName = "3533";
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
        auto nums = jread_vector(line_in);
        getline(file_in, line_in);
        auto k = jread_int(line_in);
        auto res = sol.concatenatedDivisibility(nums, k);
        getline(file_out, line_out);
        auto ans = jread_vector(line_out);
        printf("Case %d", ++caseCount);
        if (res == ans) {
            passCount++;
            printf(" %s(PASS)", KGRN);
        } else {
            printf(" %s(WRONG)", KRED);
            allPass = false;
        }
        printf("\n%s", KNRM);
        jprint_vector(res, "res");
        jprint_vector(ans, "ans");
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