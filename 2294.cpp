#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int LO = 0;
const int HI = 1e5;
bitset<100001> mp;
class Solution {
   public:
    int partitionArray(vector<int> &nums, int k) {
        int n = nums.size();
        mp.reset();
        int minV = HI + 1;
        int maxV = LO - 1;
        for (auto e : nums) {
            mp[e] = true;
            if (minV > e) {
                minV = e;
            }
            if (maxV < e) {
                maxV = e;
            }
        }
        int res = 1;
        int cur = minV;
        for (int i = minV + k + 1; i <= maxV; i++) {
            if (mp[i] > 0) {
                res++;
                i += k;
            }
        }
        return res;
    }
};

int main() {
    string problemName = "2294";
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
        auto res = sol.partitionArray(nums, k);
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