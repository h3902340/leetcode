#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define ll long long

class Solution {
   public:
    long long maxGCDScore(vector<int>& nums, int k) {
        int n = nums.size();
        ll res = 1;
        for (int i = 0; i < n; i++) {
            int a = nums[i];
            int b = twoFactor(nums[i]);
            int c = 1;
            int m = 1;
            if (c <= k) {
                m = 2;
            }
            ll score = (ll)a * m;
            if (res < score) {
                res = score;
            }
            for (int l = 1; i + l < n; l++) {
                a = gcd(a, nums[i + l]);
                int btemp = twoFactor(nums[i + l]);
                if (b == btemp) {
                    c++;
                } else if (b > btemp) {
                    b = btemp;
                    c = 1;
                }
                m = 1;
                if (c <= k) {
                    m = 2;
                }
                score = (ll)a * (l + 1) * m;
                if (res < score) {
                    res = score;
                }
            }
        }
        return res;
    }
    int gcd(int a, int b) {
        while (a != 0) {
            if (a < b) {
                swap(a, b);
            }
            a = a % b;
        }
        return b;
    }
    int twoFactor(int a) {
        int res = 0;
        while (!(a & 1)) {
            res++;
            a >>= 1;
        }
        return res;
    }
};

int main() {
    string problemName = "3574";
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
        auto res = sol.maxGCDScore(nums, k);
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