#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define ll long long
class Solution {
public:
    long long maxProfit(vector<int>& prices, vector<int>& strategy, int k) {
        int n = prices.size();
        ll res = 0;
        for (int i = 0; i < k; i++) {
            strategy[i] *= prices[i];
            res += strategy[i];
        }
        ll a = 0;
        for (int i = k; i < n; i++) {
            strategy[i] *= prices[i];
            a += strategy[i];
        }
        res += a;
        int half = k >> 1;
        for (int i = half; i < k; i++) {
            a += prices[i];
        }
        int cap = n - k;
        for (int i = 0; i < cap; i++) {
            if (res < a) {
                res = a;
            }
            a += strategy[i] - strategy[i + k] + prices[i + k] -
                 prices[i + half];
        }
        if (res < a) {
            res = a;
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