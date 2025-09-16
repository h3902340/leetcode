#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class Solution {
   public:
    vector<int> replaceNonCoprimes(vector<int>& nums) {
        int n = nums.size();
        int i = 0;
        for (int j = 1; j < n; j++) {
            int b = nums[j];
            while (i >= 0) {
                int g = gcd(nums[i], b);
                if (g == 1) {
                    break;
                }
                b = nums[i] / g * b;
                i--;
            }
            nums[++i] = b;
        }
        nums.resize(i + 1);
        return nums;
    }
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
};

int main() {
    string problemName = "2197";
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
        auto res = sol.replaceNonCoprimes(nums);
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