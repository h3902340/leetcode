#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int N = 5e5;
int prime[N + 1];
bool isInit = false;
void init() {
    prime[0] = 0;
    prime[1] = 0;
    for (int i = 2; i <= N; i++) {
        prime[i] = 1;
    }
    for (int i = 2; i <= 707; i++) {
        if (prime[i]) {
            for (int j = i + i; j <= N; j += i) {
                prime[j] = 0;
            }
        }
    }
    int s = 2;
    int mx = 2;
    prime[2] = 2;
    for (int i = 3; i <= N; i++) {
        if (prime[i]) {
            if (s < N) {
                s += i;
            }
            if (prime[i] == 2) {
                mx = i;
            }
            prime[i] = 0;
        }
        if (s <= N && prime[s]) {
            prime[s] = 2;
        }
        prime[i] = mx;
    }
}
class Solution {
   public:
    int largestPrime(int n) {
        if (!isInit) {
            init();
            isInit = true;
        }
        return prime[n];
    }
};

int main() {
    string problemName = "3770";
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
        auto res = sol.largestPrime(n);
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