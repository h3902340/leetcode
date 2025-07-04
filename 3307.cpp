#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define ll long long
#define LOG2(X) (8 * sizeof(ll) - __builtin_clzll((X)) - 1)
const int C = 26;

class Solution {
   public:
    char kthCharacter(long long k, vector<int>& operations) {
        k--;
        char res = 'a';
        while (k != 0) {
            int a = LOG2(k);
            if (operations[a] == 1) {
                res++;
                if (res > 'z') {
                    res -= C;
                }
            }
            k -= ((ll)1 << a);
        }
        return res;
    }
};

int main() {
    string problemName = "3307";
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
        auto k = jread_longlong(line_in);
        getline(file_in, line_in);
        auto operations = jread_vector(line_in);
        auto res = sol.kthCharacter(k, operations);
        getline(file_out, line_out);
        auto ans = jread_char(line_out);
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