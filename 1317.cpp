#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

vector<int> res(2);
class Solution {
   public:
    vector<int> getNoZeroIntegers(int n) {
        res[0] = 0;
        res[1] = 0;
        int m = 1;
        while (n > 1) {
            int r = n % 10;
            if (r < 2) {
                res[0] += (5 + r) * m;
                res[1] += 5 * m;
                n -= 10;
            } else {
                res[0] += m;
                res[1] += (r - 1) * m;
            }
            n /= 10;
            m *= 10;
        }
        if (n != 0) {
            res[0] += m;
        }
        return res;
    }
};

int main() {
    string problemName = "1317";
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
        auto res = sol.getNoZeroIntegers(n);
        getline(file_out, line_out);
        auto ans = jread_vector(line_out);
        bool passed = true;
        for (auto &e : res) {
            while (e > 0) {
                if (e % 10 == 0) {
                    passed = false;
                    break;
                }
                e /= 10;
            }
        }
        printf("Case %d", ++caseCount);
        if (passed) {
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