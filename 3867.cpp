#include <algorithm>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

int gcd(int a, int b) {
    int atz = __builtin_ctz(a);
    int btz = __builtin_ctz(b);
    int d = min(atz, btz);
    a >>= atz;
    b >>= btz;
    while (a != b) {
        if (a < b) {
            swap(a, b);
        }
        a -= b;
        a >>= __builtin_ctz(a);
    }
    return a <<= d;
}

class Solution {
   public:
    long long gcdSum(vector<int>& nums) {
        int n = nums.size();
        vector<int> mx(n);
        vector<int> prefixGcd(n);
        mx[0] = nums[0];
        prefixGcd[0] = gcd(nums[0], mx[0]);
        for (int i = 1; i < n; i++) {
            mx[i] = max(mx[i - 1], nums[i]);
            prefixGcd[i] = gcd(nums[i], mx[i]);
        }
        sort(begin(prefixGcd), end(prefixGcd));
        long long res = 0;
        for (int i = 0; i < (n >> 1); i++) {
            res += gcd(prefixGcd[i], prefixGcd[n - 1 - i]);
        }
        return res;
    }
};

int main() {
    string problemName = "3867";
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
        auto res = sol.gcdSum(nums);
        getline(file_out, line_out);
        auto ans = jread_longlong(line_out);
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