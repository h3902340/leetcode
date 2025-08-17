#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define ll long long
const int N = 1e5;
ll prefix[N];
ll modded[N];

class Solution {
   public:
    long long maxProfit(vector<int>& prices, vector<int>& strategy, int k) {
        int n = prices.size();
        prefix[0] = prices[0] * strategy[0];
        modded[0] = prices[0];
        for (int i = 1; i < n; i++) {
            prefix[i] = prefix[i - 1] + prices[i] * strategy[i];
            modded[i] = modded[i - 1] + prices[i];
        }
        int half = k >> 1;
        ll res = prefix[n - 1];
        for (int i = 0; i <= n - k; i++) {
            ll left = 0;
            if (i > 0) {
                left = prefix[i - 1];
            }
            ll mid = modded[k - 1 + i] - modded[half - 1 + i];
            ll right = prefix[n - 1] - prefix[k - 1 + i];
            res = max(res, left + mid + right);
        }
        return res;
    }
};

int main() {
    string problemName = "3652";
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
        auto prices = jread_vector(line_in);
        getline(file_in, line_in);
        auto strategy = jread_vector(line_in);
        getline(file_in, line_in);
        auto k = jread_int(line_in);
        auto res = sol.maxProfit(prices, strategy, k);
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