#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define ll long long
const int N = 100;
const int MASK = -1;
ll temp[N];
class Solution {
   public:
    vector<int> sortByReflection(vector<int>& nums) {
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            int a = nums[i];
            int b = 0;
            while (a > 0) {
                b = (b << 1) + (a & 1);
                a >>= 1;
            }
            temp[i] = ((ll)b << 32) | nums[i];
        }
        sort(begin(temp), begin(temp) + n);
        for (int i = 0; i < n; i++) {
            nums[i] = temp[i] & MASK;
        }
        return nums;
    }
};

int main() {
    string problemName = "3769";
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
        auto res = sol.sortByReflection(nums);
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