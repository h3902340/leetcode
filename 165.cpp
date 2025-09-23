#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int N = 500;
int v1[N >> 1];
int v2[N >> 1];

class Solution {
   public:
    int compareVersion(string version1, string version2) {
        int i = 0;
        int a = 0;
        for (auto& e : version1) {
            if (e == '.') {
                v1[i++] = a;
                a = 0;
            } else {
                a = a * 10 + (e - '0');
            }
        }
        v1[i++] = a;
        int j = 0;
        a = 0;
        for (auto& e : version2) {
            if (e == '.') {
                v2[j++] = a;
                a = 0;
            } else {
                a = a * 10 + (e - '0');
            }
        }
        v2[j++] = a;
        int cap = min(i, j);
        for (int k = 0; k < cap; k++) {
            if (v1[k] < v2[k]) {
                return -1;
            } else if (v1[k] > v2[k]) {
                return 1;
            }
        }
        if (i == j) {
            return 0;
        }
        if (i < j) {
            for (int k = cap; k < j; k++) {
                if (0 < v2[k]) {
                    return -1;
                }
            }
            return 0;
        }
        for (int k = cap; k < i; k++) {
            if (v1[k] > 0) {
                return 1;
            }
        }
        return 0;
    }
};

int main() {
    string problemName = "165";
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
        auto version1 = jread_string(line_in);
        getline(file_in, line_in);
        auto version2 = jread_string(line_in);
        auto res = sol.compareVersion(version1, version2);
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