#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int N = 5000;
long long fin[N];

class Solution {
   public:
    long long minTime(vector<int>& skill, vector<int>& mana) {
        int n = skill.size();
        int m = mana.size();
        for (int i = 1; i < n; i++) {
            skill[i] += skill[i - 1];
        }
        for (int i = 0; i < n; i++) {
            fin[i] = (long long)skill[i] * mana[0];
        }
        for (int j = 1; j < m; j++) {
            long long max = fin[0];
            for (int i = 1; i < n; i++) {
                long long t = fin[i] - (long long)skill[i - 1] * mana[j];
                if (max < t) {
                    max = t;
                }
            }
            for (int i = 0; i < n; i++) {
                fin[i] = max + (long long)skill[i] * mana[j];
            }
        }
        return fin[n - 1];
    }
};

int main() {
    string problemName = "3494";
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
        auto skill = jread_vector(line_in);
        getline(file_in, line_in);
        auto mana = jread_vector(line_in);
        auto res = sol.minTime(skill, mana);
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