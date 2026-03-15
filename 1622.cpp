#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define ll long long
const int MOD = 1e9 + 7;
const int N = 1e5;
int mul(int a, int b) { return (ll)a * b % MOD; }
int pow(int a, int b) {
    if (a == 0) return 0;
    if (a == 1) return 1;
    if (b == 0) return 1;
    if (b & 1) {
        int temp = pow(a, b - 1);
        return mul(a, temp);
    }
    int temp = pow(a, b >> 1);
    return mul(temp, temp);
}
int inv(int a) { return pow(a, MOD - 2); }
int add(int a, int b) { return (a + b) % MOD; }
int sub(int a, int b) { return (a - b + MOD) % MOD; }
int seq[N];

class Fancy {
   public:
    int i;
    int a;
    int a_inv;
    int b;
    Fancy() {
        i = 0;
        a = 1;
        a_inv = 1;
        b = 0;
    }

    void append(int val) { seq[i++] = mul(sub(val, b), a_inv); }

    void addAll(int inc) { b = add(b, inc); }

    void multAll(int m) {
        a = mul(a, m);
        a_inv = mul(a_inv, inv(m));
        b = mul(b, m);
    }

    int getIndex(int idx) {
        if (idx >= i) {
            return -1;
        }
        return add(mul(a, seq[idx]), b);
    }
};

int main() {
    string problemName = "1622";
    auto begin = jtimer();
    Fancy sol;
    bool allPass = true;
    int caseCount = 0;
    int passCount = 0;
    vector<string> cmd = {"Fancy",   "append",   "addAll",   "append",
                          "multAll", "getIndex", "addAll",   "append",
                          "multAll", "getIndex", "getIndex", "getIndex"};
    vector<vector<int>> param = {{},  {2},  {3}, {7}, {2}, {0},
                                 {3}, {10}, {2}, {0}, {1}, {2}};
    vector<string> res(cmd.size());
    vector<string> ans = {"null", "null", "null", "null", "null", "10",
                          "null", "null", "null", "26",   "34",   "20"};
    for (int i = 0; i < cmd.size(); i++) {
        string a = "null";
        if (cmd[i] == "append") {
            sol.append(param[i][0]);
        } else if (cmd[i] == "addAll") {
            sol.addAll(param[i][0]);
        } else if (cmd[i] == "multAll") {
            sol.multAll(param[i][0]);
        } else if (cmd[i] == "getIndex") {
            a = to_string(sol.getIndex(param[i][0]));
        }
        res[i] = a;
    }
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
    if (allPass) {
        printf("%sALL CORRECT [%d/%d]\n%s", KGRN, passCount, caseCount, KNRM);
    } else {
        printf("%sWRONG ANSWER [%d/%d]\n%s", KRED, passCount, caseCount, KNRM);
    }
    auto end = jtimer();
    jprint_time(begin, end);
    return 0;
}