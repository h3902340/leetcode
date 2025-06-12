#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class Solution {
   public:
    vector<int> lexicalOrder(int n) {
        vector<int> out(n);
        int d = 0;
        int a = n;
        while (a > 0) {
            d++;
            a /= 10;
        }
        out[0] = 1;
        for (int i = 1; i < n; i++) {
            int prev = out[i - 1];
            int b = prev * 10;
            if (b > n) {
                while (prev + 1 > n) {
                    prev /= 10;
                }
                prev++;
                while (prev % 10 == 0) {
                    prev /= 10;
                }
                out[i] = prev;
            } else {
                out[i] = b;
            }
        }
        return out;
    }
};

int main() {
    string problemName = "386";
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
        auto res = sol.lexicalOrder(n);
        getline(file_out, line_out);
        auto ans = jread_vector(line_out);
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