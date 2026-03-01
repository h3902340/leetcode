#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define ll long long
const int N = 1e5;
int mp[N + 1];
class Solution {
   public:
    long long countSubarrays(vector<int>& nums, int k, int m) {
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            mp[nums[i]] = 0;
        }
        int a = 0;
        int b = 0;
        int l = 0;
        ll res = 0;
        int j = 0;
        for (int i = 0; i < n; i++) {
            if (mp[nums[i]] == 0) {
                l = 0;
                a++;
            } else {
                res += l;
            }
            mp[nums[i]]++;
            if (mp[nums[i]] == m) {
                b++;
            }
            while (a > k) {
                if (mp[nums[j]] == m) {
                    b--;
                }
                mp[nums[j]]--;
                if (mp[nums[j]] == 0) {
                    a--;
                }
                j++;
            }
            while (b == k) {
                res++;
                if (mp[nums[j]] == m) {
                    break;
                }
                mp[nums[j]]--;
                if (mp[nums[j]] == 0) {
                    a--;
                }
                j++;
                l++;
            }
        }
        return res;
    }
};

int main() {
    string problemName = "3859";
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
        getline(file_in, line_in);
        auto m = jread_int(line_in);
        auto res = sol.countSubarrays(nums, k, m);
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