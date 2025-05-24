#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int PMAX = 1e5;
bool isInit = false;
vector<int> prime(PMAX, 1);
static void init() {
    if (isInit) return;
    prime[2] = 1;
    int i = 2;
    while (prime[i]) {
        for (int j = i * 2; j < PMAX; j += i) {
            prime[j] = 0;
        }
    }
    isInit = true;
}

class Solution {
   public:
    long long sumOfLargestPrimes(string s) {
        int n = s.size();
        long long p1 = 0;
        long long p2 = 0;
        long long p3 = 0;
        for (int i = n; i > 0; i--) {
            for (int j = 0; j <= n - i; j++) {
                long long num = 0;
                for (int k = j; k < j + i; k++) {
                    num = num * 10 + (s[k] - '0');
                }
                if (num == 1) continue;
                bool isPrime = true;
                long long l = 2;
                while (l * l <= num) {
                    if (num % l == 0) {
                        isPrime = false;
                        break;
                    }
                    l++;
                    if (l == PMAX) break;
                    while (!prime[l]) {
                        l++;
                    }
                }
                if (p1 == num || p2 == num || p3 == num) continue;
                if (!isPrime) continue;
                if (p1 > num) {
                    if (p2 > num) {
                        if (p3 > num) {
                            continue;
                        } else {
                            p3 = num;
                        }
                    } else {
                        p3 = p2;
                        p2 = num;
                    }
                } else {
                    p3 = p2;
                    p2 = p1;
                    p1 = num;
                }
            }
        }
        return p1 + p2 + p3;
    }
};

int main() {
    string problemName = "3554";
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
        auto s = jread_string(line_in);
        auto res = sol.sumOfLargestPrimes(s);
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
        jprint_string(s, "s");
        jprint_longlong(res, "res");
        jprint_longlong(ans, "ans");
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