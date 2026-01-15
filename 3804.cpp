#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int U = 1e5;
int cnt[(U << 1) + 1];

class Solution {
   public:
    int centeredSubarrays(vector<int>& nums) {
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            cnt[nums[i] + U] = 0;
        }
        int res = 0;
        int s = 0;
        for (int i = 0; i < n; i += 2) {
            for (int j = i; j < n; j++) {
                cnt[nums[j] + U]++;
                s += nums[j];
                if (s > U || s < -U) {
                    continue;
                }
                if (cnt[s + U] > 0) {
                    res++;
                }
            }
            cnt[nums[i] + U]--;
            s -= nums[i];
            for (int j = n - 1; j > i; j--) {
                if (s <= U && s >= -U) {
                    if (cnt[s + U] > 0) {
                        res++;
                    }
                }
                cnt[nums[j] + U]--;
                s -= nums[j];
            }
        }
        return res;
    }
};

int main() {
    string problemName = "3804";
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
        auto res = sol.centeredSubarrays(nums);
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