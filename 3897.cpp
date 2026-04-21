#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define ll long long
struct Data {
    int one;
    int zero;
    int c;
};
const int N = 1e5;
const int U = 1e4;
const int MOD = 1e9 + 7;
const auto cmp = [](Data& a, Data& b) {
    return a.one == b.one ? a.c > b.c : a.one < b.one;
};
int one[U + 1];
int zero[U + 1];
int two[U * 2 + 1];
Data arr[N];
int mul(int a, int b) { return (ll)a * b % MOD; }
int add(int a, int b) { return (a + b) % MOD; }
bool isInit = false;
void init() {
    one[0] = 0;
    zero[0] = 1;
    for (int i = 1; i <= U; i++) {
        one[i] = add(mul(one[i - 1], 2), 1);
        zero[i] = mul(zero[i - 1], 2);
    }
    two[0] = 1;
    for (int i = 1; i <= U * 2; i++) {
        two[i] = mul(two[i - 1], 2);
    }
}
class Solution {
   public:
    int maxValue(vector<int>& nums1, vector<int>& nums0) {
        if (!isInit) {
            init();
            isInit = true;
        }
        int n = nums1.size();
        int j = 0;
        int res = 0;
        for (int i = 0; i < n; i++) {
            if (nums0[i] == 0) {
                res = add(mul(res, two[nums1[i]]), one[nums1[i]]);
                continue;
            }
            arr[j++] = {nums1[i], nums0[i], nums1[i] + nums0[i]};
        }
        sort(begin(arr), begin(arr) + j, cmp);
        for (int i = j - 1; i >= 0; i--) {
            res = add(mul(res, two[arr[i].one]), one[arr[i].one]);
            res = mul(res, two[arr[i].zero]);
        }
        return res;
    }
};

int main() {
    string problemName = "3897";
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
        auto nums1 = jread_vector(line_in);
        getline(file_in, line_in);
        auto nums0 = jread_vector(line_in);
        auto res = sol.maxValue(nums1, nums0);
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