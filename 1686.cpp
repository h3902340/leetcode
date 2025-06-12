#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int MINDIFF = 2;
const int MAXDIFF = 200;
int fre[MAXDIFF + 1];

class Solution {
   public:
    int stoneGameVI(vector<int>& aliceValues, vector<int>& bobValues) {
        int n = aliceValues.size();
        int b = 0;
        for (int i = MINDIFF; i <= MAXDIFF; i++) {
            fre[i] = 0;
        }
        for (int i = 0; i < n; i++) {
            fre[aliceValues[i] + bobValues[i]]++;
            b += bobValues[i];
        }
        bool aliceTurn = true;
        for (int i = MAXDIFF; i >= MINDIFF; i--) {
            for (int j = 0; j < fre[i]; j++) {
                if (aliceTurn) {
                    b -= i;
                }
                aliceTurn = !aliceTurn;
            }
        }
        if (b < 0) {
            return 1;
        }
        if (b == 0) {
            return 0;
        }
        return -1;
    }
};

int main() {
    string problemName = "1686";
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
        auto aliceValues = jread_vector(line_in);
        getline(file_in, line_in);
        auto bobValues = jread_vector(line_in);
        auto res = sol.stoneGameVI(aliceValues, bobValues);
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