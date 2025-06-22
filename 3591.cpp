#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int NUM = 100;
bool prime[NUM + 1];
bool isInit = false;
static void init() {
    if (isInit) return;
    for (int i = 2; i <= NUM; i++) {
        prime[i] = true;
    }
    prime[1] = false;
    int nsqrt = sqrt(NUM);
    for (int i = 2; i <= nsqrt; i++) {
        if (prime[i]) {
            for (int j = i + i; j <= NUM; j += i) {
                prime[j] = false;
            }
        }
    }
    isInit = true;
}
int fre[NUM + 1];
class Solution {
   public:
    bool checkPrimeFrequency(vector<int>& nums) {
        init();
        for (int i = 0; i <= NUM; i++) {
            fre[i] = 0;
        }
        for (auto e : nums) {
            fre[e]++;
        }
        for (int i = 0; i <= NUM; i++) {
            if (prime[fre[i]]) {
                return true;
            }
        }
        return false;
    }
};

int main() {
    string problemName = "3591";
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
        auto res = sol.checkPrimeFrequency(nums);
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