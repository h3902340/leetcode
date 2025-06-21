#include <set>
#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int N = 1e5;
int odd[N];
class Solution {
   public:
    int minSwaps(vector<int> &nums) {
        int n = nums.size();
        int oddCnt = 0;
        for (int i = 0; i < n; i++) {
            if (nums[i] & 1) {
                odd[oddCnt++] = i;
            }
        }
        int evenCnt = n - oddCnt;
        if (evenCnt == oddCnt + 1) {
            int res = 0;
            int j = 1;
            for (int i = 0; i < oddCnt; i++) {
                res += abs(j - odd[i]);
                j += 2;
            }
            return res;
        }
        if (oddCnt == evenCnt + 1) {
            int res = 0;
            int j = 0;
            for (int i = 0; i < oddCnt; i++) {
                res += abs(j - odd[i]);
                j += 2;
            }
            return res;
        }
        if (oddCnt == evenCnt) {
            int res = 0;
            int j = 0;
            for (int i = 0; i < oddCnt; i++) {
                res += abs(j - odd[i]);
                j += 2;
            }
            int res2 = 0;
            j = 1;
            for (int i = 0; i < oddCnt; i++) {
                res2 += abs(j - odd[i]);
                j += 2;
            }
            return min(res, res2);
        }
        return -1;
    }
};

int main() {
    string problemName = "Q1";
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
        auto res = sol.minSwaps(nums);
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