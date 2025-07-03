#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

struct Data {
    int u;
    int i;
};
const int N = 1e5;
Data st1[N];
Data st2[N];
Data tmp[N];

class Solution {
   public:
    vector<int> secondGreaterElement(vector<int>& nums) {
        int n = nums.size();
        vector<int> res(n, -1);
        int r1 = -1;
        int r2 = -1;
        int r3 = -1;
        for (int i = 0; i < n; i++) {
            while (r2 >= 0 && st2[r2].u < nums[i]) {
                res[st2[r2].i] = nums[i];
                r2--;
            }
            while (r1 >= 0 && st1[r1].u < nums[i]) {
                tmp[++r3] = st1[r1];
                r1--;
            }
            while (r3 >= 0) {
                st2[++r2] = tmp[r3--];
            }
            st1[++r1] = {nums[i], i};
        }
        return res;
    }
};

int main() {
    string problemName = "2454";
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
        auto res = sol.secondGreaterElement(nums);
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