#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int U = 31;
int basis[U];

class Solution {
   public:
    int maxXorSubsequences(vector<int>& nums) {
        int n = nums.size();
        int res = 0;
        for (int j = U - 1; j >= 0; j--) {
            basis[j] = 0;
        }
        for (int i = 0; i < n; i++) {
            for (int j = U - 1; j >= 0; j--) {
                int mask = 1 << j;
                if ((nums[i] & mask) == 0) {
                    continue;
                }
                if (basis[j] == 0) {
                    basis[j] = nums[i];
                    break;
                }
                nums[i] ^= basis[j];
            }
        }
        for (int i = U - 1; i >= 0; i--) {
            res = max(res, res ^ basis[i]);
        }
        return res;
    }
};

int main() {
    string problemName = "3681";
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
        auto res = sol.maxXorSubsequences(nums);
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