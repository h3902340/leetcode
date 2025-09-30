#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

int mul(int a, int b, int p) { return a * b % p; }
int pow(int a, int b, int p) {
    if (a == 0) return 0;
    if (a == 1) return 1;
    if (b == 0) return 1;
    if (b & 1) {
        int temp = pow(a, b - 1, p);
        return mul(a, temp, p);
    }
    int temp = pow(a, b >> 1, p);
    return mul(temp, temp, p);
}
int inv(int a, int p) { return pow(a, p - 2, p); }

class Solution {
   public:
    int triangularSum(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) {
            return nums[0];
        }
        int a = 0;  // 2^a
        int b = 0;  // (5^b)c
        int c = 1;
        int d = 1;
        int res = nums[0] + nums[n - 1];
        for (int i = 1; i < n - 1; i++) {
            int e = n - i;
            while (e % 5 == 0) {
                e /= 5;
                b++;
            }
            c = c * e % 5;
            while (e % 2 == 0) {
                e >>= 1;
                a++;
            }
            e = i;
            while (e % 5 == 0) {
                e /= 5;
                b--;
            }
            c = c * inv(e, 5) % 5;
            while (e % 2 == 0) {
                e >>= 1;
                a--;
            }
            if (b == 0) {
                if ((a == 0 && (c % 2 == 1)) || (a > 0 && (c % 2 == 0))) {
                    d = c;
                } else {
                    d = c + 5;
                }
            } else {
                if (a == 0) {
                    d = 5;
                } else {
                    d = 0;
                }
            }
            res += nums[i] * d;
        }
        return res % 10;
    }
};

int main() {
    string problemName = "2221";
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
        auto res = sol.triangularSum(nums);
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