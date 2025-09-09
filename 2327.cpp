#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int MOD = 1e9 + 7;
const int N = 1000;
struct People {
    int day;
    int cnt;
};
struct Deque {
    int l;
    int r;
    People arr[N];
    int total;
};
Deque s;
Deque f;

class Solution {
   public:
    int peopleAwareOfSecret(int n, int delay, int forget) {
        s.l = 0;
        s.r = -1;
        f.l = 0;
        f.r = -1;
        s.arr[++s.r] = {delay, 1};
        s.total = 1;
        f.total = 0;
        int delta = forget - delay;
        for (int i = 0; i < n; i++) {
            if (s.l <= s.r && s.arr[s.l].day == i) {
                int a = s.arr[s.l].cnt;
                f.arr[++f.r] = {i + delta, a};
                s.total = sub(s.total, a);
                f.total = add(f.total, a);
                s.l++;
            }
            if (f.l <= f.r && f.arr[f.l].day == i) {
                f.total = sub(f.total, f.arr[f.l].cnt);
                f.l++;
            }
            if (f.total > 0) {
                s.arr[++s.r] = {i + delay, f.total};
                s.total = add(s.total, f.total);
            }
        }
        return add(s.total, f.total);
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
    string problemName = "2327";
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
        auto n = jread_int(line_in);
        getline(file_in, line_in);
        auto delay = jread_int(line_in);
        getline(file_in, line_in);
        auto forget = jread_int(line_in);
        auto res = sol.peopleAwareOfSecret(n, delay, forget);
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