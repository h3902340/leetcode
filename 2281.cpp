#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define ll long long
struct Data {
    int val;
    int sum;
    int cnt;
    int begin;
    int end;
};
const int MOD = 1e9 + 7;
const int N = 1e5;
Data st[N];
class Solution {
   public:
    int totalStrength(vector<int>& strength) {
        int n = strength.size();
        int begin = 0;
        int end = 0;
        int res = 0;
        int r = -1;
        int prefix = 0;
        for (int i = 0; i < n; i++) {
            Data d;
            d.val = strength[i];
            d.sum = prefix;
            prefix = add(prefix, strength[i]);
            d.cnt = 1;
            while (r >= 0 && st[r].val > d.val) {
                d.sum = add(d.sum, st[r].sum);
                d.cnt += st[r].cnt;
                begin = sub(begin, st[r].begin);
                end = sub(end, st[r].end);
                r--;
            }
            d.end = mul(d.val, d.cnt);
            d.begin = mul(d.val, d.sum);
            st[++r] = d;
            begin = add(begin, d.begin);
            end = add(end, d.end);
            res = add(res, sub(mul(end, prefix), begin));
        }
        return res;
    }
    int add(int a, int b) {
        a += b;
        if (a >= MOD) {
            a -= MOD;
        }
        return a;
    }
    int sub(int a, int b) {
        a -= b;
        if (a < 0) {
            a += MOD;
        }
        return a;
    }
    int mul(int a, int b) { return (ll)a * b % MOD; }
};

int main() {
    string problemName = "2281";
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
        auto strength = jread_vector(line_in);
        auto res = sol.totalStrength(strength);
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