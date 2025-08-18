#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

struct Fraction {
    int a;
    int b;
};
const int N = 4;
const int OPWIDTH = 2;
const int OPCNT = N - 1;
const int ALL = 1 << (OPWIDTH * OPCNT);
const int MASK = (1 << OPWIDTH) - 1;
const Fraction ERR = {0, 0};
const int POSTFIX = 2;
const int LEN = (N << 1) - 1;
// 01+2+3+, 01+23++
const int postfix[POSTFIX][LEN] = {{0, 1, 4, 2, 4, 3, 4},
                                   {0, 1, 4, 2, 3, 4, 4}};
const int WANT = 24;
Fraction nums[N];
int ops[OPCNT];
Fraction st[LEN];
int top = -1;
// time: O(N!4^N), space: O(N)
class Solution {
   public:
    bool judgePoint24(vector<int>& cards) {
        for (int i = 0; i < N; i++) {
            nums[i] = {cards[i], 1};
        }
        return perm(0);
    }
    bool perm(int i) {
        if (i == N) {
            for (int i = 0; i < ALL; i++) {
                parseOps(i);
                for (int j = 0; j < POSTFIX; j++) {
                    int opIdx = 0;
                    for (int k = 0; k < LEN; k++) {
                        int e = postfix[j][k];
                        if (e == N) {
                            Fraction& a = st[top--];
                            Fraction& b = st[top--];
                            st[++top] = op(a, b, ops[opIdx++]);
                        } else {
                            st[++top] = nums[e];
                        }
                    }
                    if (isWant(st[top--])) {
                        return true;
                    }
                }
            }
            return false;
        }
        for (int j = i; j < N; j++) {
            swap(nums[i], nums[j]);
            bool res = perm(i + 1);
            if (res) {
                return true;
            }
            swap(nums[i], nums[j]);
        }
        return false;
    }
    Fraction op(Fraction& x, Fraction& y, int opcode) {
        switch (opcode) {
            case 0:  // x+y
                return {x.a * y.b + x.b * y.a, x.b * y.b};
            case 1:  // x-y
                return {x.a * y.b - x.b * y.a, x.b * y.b};
            case 2:  // x*y
                return {x.a * y.a, x.b * y.b};
            case 3:  // x/y
                return {x.a * y.b, x.b * y.a};
        }
        return ERR;
    }
    void parseOps(int cmd) {
        for (int i = 0; i < OPCNT; i++) {
            ops[i] = cmd & MASK;
            cmd >>= OPWIDTH;
        }
    }
    bool isWant(Fraction& x) {
        return x.b != 0 && x.a % x.b == 0 && x.a / x.b == WANT;
    }
};

int main() {
    string problemName = "679";
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
        auto cards = jread_vector(line_in);
        auto res = sol.judgePoint24(cards);
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