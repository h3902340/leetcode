#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define ll long long
class Solution {
   public:
    string fractionToDecimal(int numerator, int denominator) {
        ll a = numerator;
        ll b = denominator;
        bool sign = false;
        if (a < 0 && b > 0) {
            a = -a;
            sign = true;
        } else if (a > 0 && b < 0) {
            b = -b;
            sign = true;
        }
        ll q = a / b;
        ll r = a % b;
        string res = (sign ? "-" : "") + to_string(q);
        if (r != 0) {
            res += '.';
            unordered_map<ll, int> appear;
            appear[r] = res.size();
            while (r != 0) {
                r *= 10;
                q = r / b;
                r = r % b;
                res += (q + '0');
                if (r == 0) {
                    break;
                }
                if (appear.count(r)) {
                    res.insert(appear[r], "(");
                    res += ")";
                    break;
                }
                appear[r] = res.size();
            }
        }
        return res;
    }
};

int main() {
    string problemName = "166";
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
        auto numerator = jread_int(line_in);
        getline(file_in, line_in);
        auto denominator = jread_int(line_in);
        auto res = sol.fractionToDecimal(numerator, denominator);
        getline(file_out, line_out);
        auto ans = jread_string(line_out);
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