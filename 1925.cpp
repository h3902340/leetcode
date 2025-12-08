#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int N = 250;
const int SQRTN = 16;
int arr[N + 1];
bool isInit = false;
int gcd(int a, int b) {
    int atz = __builtin_ctz(a);
    int btz = __builtin_ctz(b);
    int d = min(atz, btz);
    a >>= atz;
    b >>= btz;
    while (a != b) {
        if (a < b) {
            swap(a, b);
        }
        a -= b;
        a >>= __builtin_ctz(a);
    }
    return a <<= d;
}
void init() {
    for (int i = 0; i <= N; i++) {
        arr[i] = 0;
    }
    for (int i = 2; i < SQRTN; i += 2) {
        int a = i * i;
        for (int j = 1; j < SQRTN; j += 2) {
            int b = a + j * j;
            if (b > N) {
                break;
            }
            int g = gcd(i, j);
            if (g != 1) {
                continue;
            }
            for (int k = b; k <= N; k += b) {
                arr[k] += 2;
            }
        }
    }
    for (int i = 1; i <= N; i++) {
        arr[i] += arr[i - 1];
    }
}
class Solution {
   public:
    int countTriples(int n) {
        if (!isInit) {
            init();
            isInit = true;
        }
        return arr[n];
    }
};

int main() {
    string problemName = "1925";
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
        auto res = sol.countTriples(n);
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