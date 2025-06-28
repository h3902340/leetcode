#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

struct Data {
    int u;
    int i;
};
const int N = 1000;
Data arr[N];
bool pick[N];
class Solution {
   public:
    vector<int> maxSubsequence(vector<int>& nums, int k) {
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            arr[i] = {nums[i], i};
        }
        for (int i = 0; i < n; i++) {
            pick[i] = false;
        }
        auto cmp = [&](Data a, Data b) { return a.u > b.u; };
        sort(begin(arr), begin(arr) + n, cmp);
        for (int i = 0; i < k; i++) {
            pick[arr[i].i] = true;
        }
        vector<int> res(k);
        int j = 0;
        for (int i = 0; i < n; i++) {
            if (pick[i]) {
                res[j++] = nums[i];
                if (j == n) {
                    break;
                }
            }
        }
        return res;
    }
};

int main() {
    string problemName = "2099";
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
        auto res = sol.maxSubsequence(nums, k);
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