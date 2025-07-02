#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define ll long long
const int MOD = 1e9 + 7;
const int K = 2000;
// running length
vector<int> rl;
vector<int> pre(K - 1);
vector<int> cur(K - 1);
class Solution {
   public:
    int possibleStringCount(string word, int k) {
        int total = calcRL(word);
        int sz = rl.size();
        int goal = k - 1 - sz;
        if (goal < 0) {
            return total;
        }
        int cap = min(goal, rl[0] - 1);
        pre[0] = 1;
        for (int x = 1; x <= cap; x++) {
            pre[x] = 1;
            pre[x] = add(pre[x], pre[x - 1]);
        }
        for (int x = cap + 1; x <= goal; x++) {
            pre[x] = 0;
            pre[x] = add(pre[x], pre[x - 1]);
        }
        for (int i = 1; i < sz; i++) {
            cur[0] = 1;
            for (int x = 1; x <= goal; x++) {
                int cap = min(x, rl[i] - 1);
                cur[x] = pre[x];
                if (x != cap) {
                    cur[x] = sub(cur[x], pre[x - cap - 1]);
                }
                cur[x] = add(cur[x], cur[x - 1]);
            }
            swap(pre, cur);
        }
        return sub(total, pre[goal]);
    }
    int calcRL(string &word) {
        int n = word.size();
        rl.clear();
        int total = 1;
        int i = 0;
        while (i < n) {
            int j = i + 1;
            for (; j < n; j++) {
                if (word[i] != word[j]) {
                    break;
                }
            }
            int len = j - i;
            rl.push_back(len);
            total = mul(total, len);
            i = j;
        }
        return total;
    }
    int mul(int a, int b) {
        if (a == 0 || b == 0) {
            return 0;
        }
        return (ll)a * b % MOD;
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
};

int main() {
    string problemName = "3333";
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
        auto word = jread_string(line_in);
        getline(file_in, line_in);
        auto k = jread_int(line_in);
        auto res = sol.possibleStringCount(word, k);
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