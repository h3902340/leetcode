#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int N = 1e5;
const int U = 1e5;
int fre[U + 1];
int frefre[N + 1];

class Solution {
   public:
    int firstUniqueFreq(vector<int>& nums) {
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            fre[nums[i]] = 0;
        }
        for (int i = 0; i < n; i++) {
            fre[nums[i]]++;
            if (fre[nums[i]] > 1) {
                nums[i] = 0;
            }
        }
        for (int i = 0; i < n; i++) {
            frefre[fre[nums[i]]] = 0;
        }
        for (int i = 0; i < n; i++) {
            frefre[fre[nums[i]]]++;
        }
        for (int i = 0; i < n; i++) {
            if (frefre[fre[nums[i]]] == 1) {
                return nums[i];
            }
        }
        return -1;
    }
};

int main() {
    string problemName = "3843";
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
        auto res = sol.firstUniqueFreq(nums);
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