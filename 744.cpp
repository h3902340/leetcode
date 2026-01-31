#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const char U = 'z' + 1;

class Solution {
   public:
    char nextGreatestLetter(vector<char>& letters, char target) {
        int n = letters.size();
        char res = U;
        for (int i = 0; i < n; i++) {
            if (letters[i] > target) {
                if (res > letters[i]) {
                    res = letters[i];
                }
            }
        }
        if (res == U) {
            return letters[0];
        }
        return res;
    }
};

int main() {
    string problemName = "744";
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
        auto letters = jread_vector_char(line_in);
        getline(file_in, line_in);
        auto target = jread_char(line_in);
        auto res = sol.nextGreatestLetter(letters, target);
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