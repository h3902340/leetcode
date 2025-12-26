#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class Solution {
   public:
    int minSwaps(vector<int>& nums, vector<int>& forbidden) {
        int n = nums.size();
        int can = 0;
        int cnt = 0;
        int tot = 0;
        for (int i = 0; i < n; i++) {
            if (nums[i] == forbidden[i]) {
                tot++;
                if (cnt == 0) {
                    cnt++;
                    can = nums[i];
                } else {
                    if (can == nums[i]) {
                        cnt++;
                    } else {
                        cnt--;
                    }
                }
            }
        }
        int avail = 0;
        cnt = 0;
        for (int i = 0; i < n; i++) {
            if (nums[i] == can) {
                if (forbidden[i] == can) {
                    cnt++;
                }
            } else {
                if (forbidden[i] != can) {
                    avail++;
                }
            }
        }
        if (cnt > avail) {
            return -1;
        }
        if (cnt > tot - cnt) {
            return cnt;
        }
        return (tot + 1) >> 1;
    }
};

int main() {
    string problemName = "3785";
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
        auto forbidden = jread_vector(line_in);
        auto res = sol.minSwaps(nums, forbidden);
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