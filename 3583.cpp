#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define ll long long
const int MOD = 1e9 + 7;
class Solution {
   public:
    int specialTriplets(vector<int>& nums) {
        int res = 0;
        int fre[100001]{0};
        int fre2[100001]{0};
        for (auto e : nums) {
            fre[e]++;
        }
        for (auto e : nums) {
            if (e == 0) {
                res += (ll)fre2[e] * (fre[e] - 1 - fre2[e]) % MOD;
            } else {
                int e2 = e << 1;
                if (e2 < 100001) {
                    res += (ll)fre2[e2] * (fre[e2] - fre2[e2]) % MOD;
                }
            }
            if (res >= MOD) {
                res -= MOD;
            }
            fre2[e]++;
        }
        return res;
    }
};

int main() {
    string problemName = "3583";
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
        auto res = sol.specialTriplets(nums);
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