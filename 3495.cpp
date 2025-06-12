#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class Solution {
   public:
    long long minOperations(vector<vector<int>>& queries) {
        long long res = 0;
        for (auto& e : queries) {
            long long sum = 0;
            int l = e[0];
            int r = e[1];
            long long a = 1;
            int b = 0;
            while (l <= r) {
                while (a <= l) {
                    a <<= 2;
                    b++;
                }
                if (a <= r) {
                    sum += (a - l) * b;
                    l = a;
                } else {
                    sum += (long long)(r - l + 1) * b;
                    break;
                }
            }
            res += (sum + 1) >> 1;
        }
        return res;
    }
};

int main() {
    string problemName = "3495";
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
        auto queries = jread_vector2d(line_in);
        auto res = sol.minOperations(queries);
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