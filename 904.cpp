#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class Solution {
   public:
    int totalFruit(vector<int>& fruits) {
        int n = fruits.size();
        int i = 0;
        int a = -1;
        int b = -1;
        int ac = 0;
        int bc = 0;
        int res = 0;
        for (int j = 0; j < n; j++) {
            if (a == -1) {
                a = fruits[j];
                ac = 1;
            } else {
                if (a == fruits[j]) {
                    ac++;
                } else {
                    if (b == -1) {
                        b = fruits[j];
                        bc = 1;
                    } else {
                        if (b == fruits[j]) {
                            bc++;
                        } else {
                            int total = ac + bc;
                            if (res < total) {
                                res = total;
                            }
                            while (ac > 0 && bc > 0) {
                                if (a == fruits[i]) {
                                    ac--;
                                } else if (b == fruits[i]) {
                                    bc--;
                                }
                                i++;
                            }
                            if (ac == 0) {
                                a = fruits[j];
                                ac = 1;
                            } else {
                                b = fruits[j];
                                bc = 1;
                            }
                        }
                    }
                }
            }
        }
        int total = ac + bc;
        if (res < total) {
            res = total;
        }
        return res;
    }
};

int main() {
    string problemName = "904";
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
        auto fruits = jread_vector(line_in);
        auto res = sol.totalFruit(fruits);
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