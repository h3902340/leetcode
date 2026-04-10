#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int N = 100;
int mp[N + 1][3];
class Solution {
   public:
    int minimumDistance(vector<int>& nums) {
        int n = nums.size();
        for (int i = 1; i <= n; i++) {
            mp[i][0] = -1;
            mp[i][1] = -1;
            mp[i][2] = -1;
        }
        int res = -1;
        for (int i = 0; i < n; i++) {
            mp[nums[i]][0] = mp[nums[i]][1];
            mp[nums[i]][1] = mp[nums[i]][2];
            mp[nums[i]][2] = i;
            if (mp[nums[i]][0] != -1) {
                int a = (i - mp[nums[i]][0]) * 2;
                if (res == -1 || res > a) {
                    res = a;
                }
            }
        }
        return res;
    }
};

int main() {
    string problemName = "3740";
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
        auto res = sol.minimumDistance(nums);
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