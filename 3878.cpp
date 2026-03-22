#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define ll long long
class Solution {
   public:
    long long countGoodSubarrays(vector<int>& nums) {
        int n = nums.size();
        vector<int> r(n, n);
        vector<int> l(n, -1);
        stack<int> st;
        for (int i = 0; i < n; i++) {
            while (!st.empty()) {
                if ((nums[st.top()] & nums[i]) == nums[i]) {
                    break;
                }
                r[st.top()] = i;
                st.pop();
            }
            st.push(i);
        }
        st = stack<int>();
        for (int i = n - 1; i >= 0; i--) {
            while (!st.empty()) {
                if ((nums[st.top()] & nums[i]) == nums[i]) {
                    if (nums[st.top()] != nums[i]) {
                        break;
                    }
                }
                l[st.top()] = i;
                st.pop();
            }
            st.push(i);
        }
        ll res = 0;
        for (int i = 0; i < n; i++) {
            res += (ll)(r[i] - i) * (i - l[i]);
        }
        return res;
    }
};

int main() {
    string problemName = "3878";
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
        auto res = sol.countGoodSubarrays(nums);
        getline(file_out, line_out);
        auto ans = jread_longlong(line_out);
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