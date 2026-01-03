#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define ll long long
const int U = 1e5;
int mp[U + 1];
class Solution {
   public:
    int minLength(vector<int>& nums, int k) {
        int n = nums.size();
        int j = 0;
        ll sum = 0;
        int res = -1;
        for (int i = 0; i < n; i++) {
            mp[nums[i]] = 0;
        }
        for (int i = 0; i < n; i++) {
            if (mp[nums[i]] == 0) {
                sum += nums[i];
            }
            mp[nums[i]]++;
            while (sum >= k) {
                if (mp[nums[j]] == 1) {
                    if (sum - nums[j] < k) {
                        break;
                    }
                    sum -= nums[j];
                }
                mp[nums[j]]--;
                j++;
            }
            if (sum >= k) {
                int l = i - j + 1;
                if (res == -1 || res > l) {
                    res = l;
                }
            }
        }
        return res;
    }
};

int main() {
    string problemName = "3795";
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
        auto res = sol.minLength(nums, k);
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