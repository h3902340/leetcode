#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define ll long long
class Solution {
   public:
    vector<long long> distance(vector<int>& nums) {
        int n = nums.size();
        unordered_map<int, ll> s;
        unordered_map<int, int> c;
        for (int i = 0; i < n; i++) {
            s[nums[i]] += i;
            c[nums[i]]++;
        }
        vector<ll> res(n);
        for (int i = n - 1; i >= 0; i--) {
            res[i] = (ll)c[nums[i]] * i - s[nums[i]];
            s[nums[i]] -= i * 2;
            c[nums[i]] -= 2;
        }
        return res;
    }
};

int main() {
    string problemName = "2615";
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
        auto res = sol.distance(nums);
        getline(file_out, line_out);
        auto ans = jread_vector_longlong(line_out);
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