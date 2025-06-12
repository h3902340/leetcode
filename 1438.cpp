#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

// Based on lee's solution
const int N = 1e5;
int qmax[N];
int qmin[N];

class Solution {
   public:
    int longestSubarray(vector<int>& nums, int limit) {
        int n = nums.size();
        int lmax = 0;
        int rmax = -1;
        int lmin = 0;
        int rmin = -1;
        int i = 0;
        int j = 0;
        for (; j < n; j++) {
            int e = nums[j];
            while (lmax <= rmax && qmax[rmax] < e) {
                rmax--;
            }
            while (lmin <= rmin && qmin[rmin] > e) {
                rmin--;
            }
            qmax[++rmax] = e;
            qmin[++rmin] = e;
            if (qmax[lmax] - qmin[lmin] > limit) {
                if (qmax[lmax] == nums[i]) {
                    lmax++;
                }
                if (qmin[lmin] == nums[i]) {
                    lmin++;
                }
                i++;
            }
        }
        return j - i;
    }
};

int main() {
    string problemName = "1438";
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
        auto limit = jread_int(line_in);
        auto res = sol.longestSubarray(nums, limit);
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