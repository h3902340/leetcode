#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class Solution {
   public:
    bool canMakeEqual(vector<int>& nums, int k) {
        return f(nums, k, 1) || f(nums, k, -1);
    }
    bool f(vector<int>& nums, int k, int a) {
        int n = nums.size();
        int c = 0;
        vector<int> indexes;
        for (int i = 0; i < n; i++) {
            if (nums[i] == a) {
                c++;
                indexes.push_back(i);
            }
        }
        if (c & 1) return false;
        int d = 0;
        for (int i = 0; i < indexes.size(); i += 2) {
            d += indexes[i + 1] - indexes[i];
        }
        if (d > k) {
            return false;
        }
        return true;
    }
};

int main() {
    string problemName = "3576";
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
        auto res = sol.canMakeEqual(nums, k);
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